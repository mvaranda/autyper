/*
 * libmad - MPEG audio decoder library
 * Copyright (C) 2000-2004 Underbit Technologies, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: minimad.c,v 1.4 2004/01/23 09:41:32 rob Exp $
 */

# include <stdio.h>
# include <unistd.h>
# include <malloc.h>
#include <math.h>
//# include <sys/stat.h>
//# include <sys/mman.h>

# include "mad.h"

/*
 * This is perhaps the simplest example use of the MAD high-level API.
 * Standard input is mapped into memory via mmap(), then the high-level API
 * is invoked with three callbacks: input, output, and error. The output
 * callback converts MAD's high-resolution PCM samples to 16 bits, then
 * writes them to standard output in little-endian, stereo-interleaved
 * format.
 */

static int decode(unsigned char const *, unsigned long);

#define MAX_FILE_SIZE (1024 * 1024 * 10) // 10 Mbytes
#define FILE_NAME "..\\voices\\invisibleman_Stereo_44100_32_256kbs.mp3"
#define FILE_OUTPUT "samples.raw"

#define LOG printf

static FILE * f_out;

static int resample(  char * filename, unsigned int samplerate_in,
                      char * file_out, unsigned int samplerate_out);


static int mp3ToRaw( char * filename, char * file_out)
{
  unsigned long len;
  void *fdm;
  
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
  
  fdm = malloc(len);
  if (! fdm) {
    LOG("Could not allocate memory\n");
    return 1;
  }
  
  int nread = fread(fdm, 1, len, fh);
  fclose(fh);
  if (nread != len) {
    LOG("Could not read %d bytes, read instead %d\n", len, nread);
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

static unsigned int input_samplerate;

int main(int argc, char *argv[])
{
  
  char * filename = FILE_NAME;
  char * file_out = FILE_OUTPUT;
  
  if (argc >= 2) filename = argv[1];
  if (argc >= 3) file_out = argv[2];
  
  LOG("input: \"%s\"\n", filename);
  LOG("output: \"%s\"\n", file_out);
  if ( mp3ToRaw(filename, file_out) == 0) {
  
    return resample(  file_out, input_samplerate,
                      "out_16K.raw", 16000);
  }
  
  return 1; //mp2ToRaw fail

}

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
  struct buffer *buffer = data;

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
    LOG("Parameters:\n  samplerate = %d  nchannels = %d\n  nsamples = %d\n  left_ch = 0x%x\n  right_ch = 0x%x\n\n",
      input_samplerate, nchannels, nsamples, left_ch, right_ch);
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
  struct buffer *buffer = data;

  fprintf(stderr, "decoding error 0x%04x (%s) at byte offset %u\n",
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

/*

Resample definitions:
                     |<St->|
                     |     |
Source samples:      T0    T1    T2    T3    T4    T5    T6    T7    T8
                     |     |     |     |     |     |     |     |     |
+20                        -------     |
+10                       /       \    |    -#------
0                     ---          \   |   /        \
-10                  /              \  |  /          -----
-20                                  \ | *<--VD2     
-30                                   -#-|       
                                         |        
Destination samples: D0        D1        D2        D3        D4        T5        T6        T7      T8
                     |         |         |         |         |         |         |         |       |
                     |                   |
                     |<-------- T ------>|
     
St = original sample period, ex: 1/44100

S = source sample array (holding values for T0, T1... TN)
i = Src sample index
VD2 = desired destination sample value at D2
T = time for desired sample D2 value to be calculated
V = src sample before T (sample # at T3)
Vn = src sample after T (sample # at T4)
Vd = delta (Vn- V)

then:
  i = T/St
  V = S[ int(i) ]
  Vn = S[ int(i + 1) ]
  Vd = Vn - V
  VD2 = V + (  (T - int(i) * St) / St  ) * Vd
  
  ex: St = 60 microseconds (16666 Hz)
      destination period = 100 microseconds (10000Hz)
      T = 200
      V = S[ int( 200/60 ) ]
      V = S[ int(3.33) ]
      V = S[ 3 ] = -30
      V = -30
      Vn = S[ int(4.33) ]
      Vn = +10
      Vd = 10 - (-30)
      Vd = 40
      VD2 = -30 + (  (200 - 3 * 60) / 60  ) * 40
      VD2 = -30 + 0.3333 * 40
      VD2 = -30 + 13.333
      VD2 = -16.66
      
     
  
*/

#define RESAMPLE_NUM_SAMPLES (1024 * 128)

typedef short sample_t; // two bytes per sample

static sample_t bufin[RESAMPLE_NUM_SAMPLES];
static sample_t bufout[RESAMPLE_NUM_SAMPLES];

static int resample(  char * filename, unsigned int samplerate_in,
                      char * file_out, unsigned int samplerate_out)
{
  double St = 1.0 / samplerate_in;
  double StBase = 0.0;
  double i = 0.0;
  double T = 0.0;
  double Dp = 1.0 / samplerate_out; // destination period
  unsigned int s_idx;
  sample_t         V, Vn, Vd, VD2;
  
  unsigned int samples_available_space = RESAMPLE_NUM_SAMPLES;
  
  if (samplerate_out >= samplerate_in) {
    LOG("resample: output sample rate %d must be lower than input's %d.\n", samplerate_out, samplerate_in);
    return 1;
  }
 
  void *fdm;
  unsigned int nread, nsamples;
  double integer;
  
  FILE * fh = fopen(filename, "rb");
  if (! fh) {
    LOG("resample: Could not open input file: \"%s\"\n", filename);
    return 1;
  }
  
  f_out = fopen(file_out, "wb");
  if (! f_out) {
    LOG("resample: Could not open output file: \"%s\"\n", file_out);
    return 1;
  }
  
  // we read 1 sample as the loop will always bring the last 
  
  while ( (nread = fread( &bufin[RESAMPLE_NUM_SAMPLES - samples_available_space], sizeof(sample_t), samples_available_space, fh) ) > 0) {
    nsamples = nread/sizeof(sample_t);
    if (nsamples < 4) {
      LOG("resample: less than 4 samples remaining... drop them.\n");
      break;
    }
    
    LOG("nsamples = %d\n", nsamples);
    
    while (1) {
    
      // i = T/St
      i = T/St;
    
      // V = S[ int(i) ]
      modf(i, &integer);
      if (integer >= RESAMPLE_NUM_SAMPLES) {
        LOG("Before sample not available\n");
        //StBase += St * nsamples;
        samples_available_space = RESAMPLE_NUM_SAMPLES;
        T -= St * nsamples;
        while (T < 0) T += Dp;
        //feed_more = 1;
        break;
      }
      V = bufin[ (int) integer ];
      double int_i__times__St = integer * St;
    
      // Vn = S[ int(i + 1) ]
      modf(i + 1.0, &integer);
      if (integer >= RESAMPLE_NUM_SAMPLES) {
        LOG("After sample not available\n");
        // we need to move the last sample to the begining
        bufin[0] = V;
        //StBase += St * (nsamples - 1);
        samples_available_space = RESAMPLE_NUM_SAMPLES - 1;
        T -= St * (nsamples - 1);
        while (T < 0) T += Dp;
        //feed_more = 1;        
        break;
      }
      Vn = bufin[ (int) integer ];
    
      // Vd = Vn - V
      Vd = Vn - V;
    
      // VD2 = V + (  (T - int(i) * St) / St  ) * Vd
      VD2 = (sample_t) (  V + ( (T - int_i__times__St) / St) * Vd  );
      
#if 0
      if (T < 1.5) {
        LOG( "Vn = %d\n", Vn);
        LOG( "V = %d\n", V);
        LOG( "Vd = %d\n", Vd);
        LOG( "VD2 = %d\n", VD2);
        
        LOG( "int_i__times__St = %f\n", int_i__times__St);
        LOG( "T = %f\n", T);
        LOG( "i = %f\n", i);
        
        LOG( "St = %f\n\n", St);
      }
#endif

      fwrite(&VD2, sizeof(sample_t), 1, f_out);
      //      fwrite(&V, sizeof(sample_t), 1, f_out);
    
      T += Dp;
    }
    
    /*  i = T/St
        V = S[ int(i) ]
        Vn = S[ int(i + 1) ]
        Vd = Vn - V
        VD2 = V + (  (T - int(i) * St) / St  ) * Vd
    */
    LOG("new block\n");
    
    
  }
  fclose(fh);
  fclose(f_out);
  
  return 0;
}
