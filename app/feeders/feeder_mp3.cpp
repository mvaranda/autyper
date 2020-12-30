/*
 * This file is part of the AuTyper distribution (https://github.com/mvaranda/autyper).
 * Copyright (c) 2020 Marcelo Varanda.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QProcessEnvironment>
#include "feeder_mp3.h"
#include "log.h"

extern "C" {
  #include "mad.h"
  unsigned int getMp3SampleRate( void );
  FILE * convertMp3ToRaw(const char * mp3file, const char * path);
}

#ifdef _MACOS
  #include <malloc/malloc.h>
#else
  #include <malloc.h>
#endif



#define MAX_FILE_SIZE                   (1024 * 1024 * 10) // 10 Mbytes
#define FILE_RAW_FROM_MP3               "\\samples.$$$"
#define FILE_RAW_FROM_RESAMPLER         "\\samples.raw"
#define DEEPSPEECH_SAMPLERATE           16000

FeederMp3::FeederMp3(QString input):FeederBase(input)
{
  QProcessEnvironment p;
  QString fp = p.systemEnvironment().value(QString("TEMP"));
  samples_fh = convertMp3ToRaw(input.toStdString().c_str(), (const char *) fp.toStdString().c_str());
  if (samples_fh == NULL) {
    throw FeederException("Fail to convert MP3 file", 0);
  }

}

feeder_res_t FeederMp3::getSamples(sample_t * samples, uint32_t num_samples, int progress)
{

}


//=================== from libmad sample ==================

extern "C" {

  static FILE * f_out;
  static unsigned int input_samplerate = 0;

  unsigned int getMp3SampleRate( void ) {return input_samplerate; }

  /*
   * This is a private message structure. A generic pointer to this structure
   * is passed to each of the callback functions. Put here any data you need
   * to access from within the callbacks.
   */

  struct buffer {
    unsigned char const *start;
    unsigned long length;
  };

  /*
   * This is the input callback. The purpose of this callback is to (re)fill
   * the stream buffer which is to be decoded. In this example, an entire file
   * has been mapped into memory, so we just call mad_stream_buffer() with the
   * address and length of the mapping. When this callback is called a second
   * time, we are finished decoding.
   */

  static
  enum mad_flow input(void *data,
          struct mad_stream *stream)
  {
    struct buffer *buffer = (struct buffer *) data;

    if (!buffer->length)
      return MAD_FLOW_STOP;

    mad_stream_buffer(stream, buffer->start, buffer->length);

    buffer->length = 0;

    return MAD_FLOW_CONTINUE;
  }

  /*
   * The following utility routine performs simple rounding, clipping, and
   * scaling of MAD's high-resolution samples down to 16 bits. It does not
   * perform any dithering or noise shaping, which would be recommended to
   * obtain any exceptional audio quality. It is therefore not recommended to
   * use this routine if high-quality output is desired.
   */

  static inline
  signed int scale(mad_fixed_t sample)
  {
    /* round */
    sample += (1L << (MAD_F_FRACBITS - 16));

    /* clip */
    if (sample >= MAD_F_ONE)
      sample = MAD_F_ONE - 1;
    else if (sample < -MAD_F_ONE)
      sample = -MAD_F_ONE;

    /* quantize */
    return sample >> (MAD_F_FRACBITS + 1 - 16);
  }

  /*
   * This is the output callback function. It is called after each frame of
   * MPEG audio data has been completely decoded. The purpose of this callback
   * is to output (or play) the decoded PCM audio.
   */

  static
  enum mad_flow output(void *data,
           struct mad_header const *header,
           struct mad_pcm *pcm)
  {
    unsigned int nchannels, nsamples;
    mad_fixed_t const *left_ch, *right_ch;
    static int first_time = 1;

    nchannels = pcm->channels;
    nsamples  = pcm->length;
    left_ch   = pcm->samples[0];
    right_ch  = pcm->samples[1];

    if (first_time) {
      first_time = 0;
      input_samplerate = pcm->samplerate;
  //    LOG("Parameters:\n  samplerate = %d  nchannels = %d\n  nsamples = %d\n  left_ch = 0x%x\n  right_ch = 0x%x\n\n",
  //      input_samplerate, nchannels, nsamples, (unsigned int) left_ch, (unsigned int) right_ch);
    }

    while (nsamples--) {
      signed int sample1;
      signed int sample2;

      /* output sample(s) in 16-bit signed little-endian PCM */

      sample1 = scale(*left_ch++);
      if (nchannels > 1) {
        sample2 = scale(*right_ch++);
        sample1 = (sample1/2) + (sample2/2); // to mono
      }

      if (fwrite(&sample1, 1, 2, f_out) != 2) {
        LOG("write error\n");
      }

    }

    return MAD_FLOW_CONTINUE;
  }

  /*
   * This is the error callback function. It is called whenever a decoding
   * error occurs. The error is indicated by stream->error; the list of
   * possible MAD_ERROR_* errors can be found in the mad.h (or stream.h)
   * header file.
   */

  static
  enum mad_flow error(void *data,
          struct mad_stream *stream,
          struct mad_frame *frame)
  {
    struct buffer *buffer = (struct buffer *) data;

    fprintf(stderr, "decoding error 0x%04x (%s) at byte offset %I64u\n",
      stream->error, mad_stream_errorstr(stream),
      stream->this_frame - buffer->start);

    /* return MAD_FLOW_BREAK here to stop decoding (and propagate an error) */

    return MAD_FLOW_CONTINUE;
  }

  /*
   * This is the function called by main() above to perform all the decoding.
   * It instantiates a decoder object and configures it with the input,
   * output, and error callback functions above. A single call to
   * mad_decoder_run() continues until a callback function returns
   * MAD_FLOW_STOP (to stop decoding) or MAD_FLOW_BREAK (to stop decoding and
   * signal an error).
   */

  static
  int decode(unsigned char const *start, unsigned long length)
  {
    struct buffer buffer;
    struct mad_decoder decoder;
    int result;

    /* initialize our private message structure */

    buffer.start  = start;
    buffer.length = length;

    /* configure input, output, and error functions */

    mad_decoder_init(&decoder, &buffer,
         input, 0 /* header */, 0 /* filter */, output,
         error, 0 /* message */);

    /* start decoding */

    result = mad_decoder_run(&decoder, MAD_DECODER_MODE_SYNC);

    /* release the decoder */

    mad_decoder_finish(&decoder);

    return result;
  }


  static int mp3ToRaw( const char * filename, const char * file_out)
  {
    unsigned long len;
    unsigned char *fdm;

    FILE * fh = fopen(filename, "rb");
    if (! fh) {
      LOG("Could not open input file: \"%s\"\n", filename);
      return 1;
    }
    fseek(fh, 0, SEEK_END);
    len = ftell(fh);
    fseek(fh, 0, SEEK_SET);

    if (len == 0) {
      LOG("Input file len = 0\n");
      return 1;
    }

    if (len > MAX_FILE_SIZE) {
      LOG("Input file too large. must be < 10MBytes\n");
      return 1;
    }

    fdm = (unsigned char *) malloc(len);
    if (! fdm) {
      LOG("Could not allocate memory\n");
      return 1;
    }

    int nread = fread(fdm, 1, len, fh);
    fclose(fh);
    if (nread != len) {
      LOG("Could not read %ld bytes, read instead %d\n", len, nread);
      return 1;
    }

    f_out = fopen(file_out, "wb");
    if (! f_out) {
      LOG("Could not open output file: \"%s\"\n", file_out);
      return 1;
    }

    decode(fdm, len);
    fclose(f_out);

    return 0;
  }
  //#define FILE_RAW_FROM_MP3         "\\samples.$$$"
//#define FILE_RAW_FROM_RESAMPLER   "\\samples.raw"

  FILE * convertMp3ToRaw(const char * mp3file, const char * path)
  {
    FILE * raw_file_h = NULL;
    char filename[512];
    char resample_file[512];
    strncpy(filename, path, sizeof(filename));
    int len = strlen(filename);
    if ((len + strlen(FILE_RAW_FROM_RESAMPLER) + 1) > sizeof(filename)) {
      LOG("Filename too long\n");
      return NULL;
    }
    strcat(filename, FILE_RAW_FROM_MP3);

    if ( mp3ToRaw(mp3file, filename) != 0) {
      return NULL;
    }

    if (DEEPSPEECH_SAMPLERATE == input_samplerate) { // no need to resample
      return (fopen(filename, "rb"));
    }

    //
    strncpy(resample_file, path, sizeof(resample_file));
    strcat(resample_file, FILE_RAW_FROM_RESAMPLER);

    if (resample(  filename, input_samplerate,
                       resample_file, DEEPSPEECH_SAMPLERATE)) {
      return NULL;
    }

    return  (fopen(resample_file, "rb"));
  }

}
