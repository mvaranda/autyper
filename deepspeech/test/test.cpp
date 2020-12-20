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


#include <stdlib.h>
#include <stdio.h>

#include <assert.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sstream>
#include <string>

#define _MSC_VER


#include "deepspeech.h"

#define NO_SOX
#define NO_DIR

#ifdef QT_APP
  #include "log.h"
#else
  #define LOG         printf
  #define LOG_E       printf
  #define LOG_I       printf
  #define LOG_W       printf
#endif

#if 0
int main()
{

  LOG("Test\n");
  ModelState* aCtx = NULL;
      StreamingState* ctx;
    int status = DS_CreateStream(aCtx, &ctx);
    if (status != DS_ERR_OK) {
      LOG("error\n");
      return 1;
    }

  return 0;
}

#else

typedef struct {
  const char* string;
  double cpu_time_overall;
} ds_result;


typedef struct {
  char*  buffer;
  size_t buffer_size;
} ds_audio_buffer;


bool set_beamwidth = false;
int beam_width = 0;
bool set_alphabeta = false;
float lm_alpha = 0.f;
float lm_beta = 0.f;
bool show_times = false;
bool has_versions = false;
bool extended_metadata = false;
bool json_output = false;
int json_candidate_transcripts = 3;
int stream_size = 0;
int extended_stream_size = 0;
char* hot_words = NULL;

char* CandidateTranscriptToString(const CandidateTranscript* transcript)
{
  std::string retval = "";
  for (int i = 0; i < transcript->num_tokens; i++) {
    const TokenMetadata& token = transcript->tokens[i];
    retval += token.text;
  }
  return strdup(retval.c_str());
}


ds_result LocalDsSTT(ModelState* aCtx, const short* aBuffer, size_t aBufferSize,
           bool extended_output, bool json_output)
{
  ds_result res = {0};

  clock_t ds_start_time = clock();

  // sphinx-doc: c_ref_inference_start
  if (extended_output) {
    Metadata *result = DS_SpeechToTextWithMetadata(aCtx, aBuffer, aBufferSize, 1);
    res.string = CandidateTranscriptToString(&result->transcripts[0]);
    DS_FreeMetadata(result);
  } else if (json_output) {
    // Metadata *result = DS_SpeechToTextWithMetadata(aCtx, aBuffer, aBufferSize, json_candidate_transcripts);
    // res.string = MetadataToJSON(result);
    // DS_FreeMetadata(result);
  } else if (stream_size > 0) {
    StreamingState* ctx;
    int status = DS_CreateStream(aCtx, &ctx);
    if (status != DS_ERR_OK) {
      res.string = strdup("");
      return res;
    }
    size_t off = 0;
    const char *last = nullptr;
    const char *prev = nullptr;
    while (off < aBufferSize) {
      size_t cur = aBufferSize - off > stream_size ? stream_size : aBufferSize - off;
      DS_FeedAudioContent(ctx, aBuffer + off, cur);
      off += cur;
      prev = last;
      const char* partial = DS_IntermediateDecode(ctx);
      if (last == nullptr || strcmp(last, partial)) {
        LOG("%s\n", partial);
        last = partial;
      } else {
        DS_FreeString((char *) partial);
      }
      if (prev != nullptr && prev != last) {
        DS_FreeString((char *) prev);
      }
    }
    if (last != nullptr) {
      DS_FreeString((char *) last);
    }
    res.string = DS_FinishStream(ctx);
  } else if (extended_stream_size > 0) {
    StreamingState* ctx;
    int status = DS_CreateStream(aCtx, &ctx);
    if (status != DS_ERR_OK) {
      res.string = strdup("");
      return res;
    }
    size_t off = 0;
    const char *last = nullptr;
    const char *prev = nullptr;
    while (off < aBufferSize) {
      size_t cur = aBufferSize - off > extended_stream_size ? extended_stream_size : aBufferSize - off;
      DS_FeedAudioContent(ctx, aBuffer + off, cur);
      off += cur;
      prev = last;
      const Metadata* result = DS_IntermediateDecodeWithMetadata(ctx, 1);
      const char* partial = CandidateTranscriptToString(&result->transcripts[0]);
      if (last == nullptr || strcmp(last, partial)) {
        LOG("%s\n", partial);
       last = partial;
      } else {
        free((char *) partial);
      }
      if (prev != nullptr && prev != last) {
        free((char *) prev);
      }
      DS_FreeMetadata((Metadata *)result);
    }
    const Metadata* result = DS_FinishStreamWithMetadata(ctx, 1);
    res.string = CandidateTranscriptToString(&result->transcripts[0]);
    DS_FreeMetadata((Metadata *)result);
    free((char *) last);
  } else {
    res.string = DS_SpeechToText(aCtx, aBuffer, aBufferSize);
  }
  // sphinx-doc: c_ref_inference_stop

  clock_t ds_end_infer = clock();

  res.cpu_time_overall =
    ((double) (ds_end_infer - ds_start_time)) / CLOCKS_PER_SEC;

  return res;
}

ds_audio_buffer GetAudioBuffer(const char* path, int desired_sample_rate)
{
  ds_audio_buffer res = {0};
  
  // FIXME: Hack and support only mono 16-bits PCM with standard SoX header
  FILE* wave = fopen(path, "r");

  size_t rv;

  unsigned short audio_format;
  fseek(wave, 20, SEEK_SET); rv = fread(&audio_format, 2, 1, wave);

  unsigned short num_channels;
  fseek(wave, 22, SEEK_SET); rv = fread(&num_channels, 2, 1, wave);

  unsigned int sample_rate;
  fseek(wave, 24, SEEK_SET); rv = fread(&sample_rate, 4, 1, wave);

  unsigned short bits_per_sample;
  fseek(wave, 34, SEEK_SET); rv = fread(&bits_per_sample, 2, 1, wave);

  assert(audio_format == 1); // 1 is PCM
  assert(num_channels == 1); // MONO
  assert(sample_rate == desired_sample_rate); // at desired sample rate
  assert(bits_per_sample == 16); // 16 bits per sample

  LOG_E("audio_format=%d\n", audio_format);
  LOG_E("num_channels=%d\n", num_channels);
  LOG_E("sample_rate=%d (desired=%d)\n", sample_rate, desired_sample_rate);
  LOG_E("bits_per_sample=%d\n", bits_per_sample);

  fseek(wave, 40, SEEK_SET); rv = fread(&res.buffer_size, 4, 1, wave);
  LOG_E("res.buffer_size=%ld\n", res.buffer_size);

  fseek(wave, 44, SEEK_SET);
  res.buffer = (char*)malloc(sizeof(char) * res.buffer_size);
  rv = fread(res.buffer, sizeof(char), res.buffer_size, wave);

  fclose(wave);
  return res;
}

void ProcessFile(ModelState* context, const char* path, bool show_times)
{
  ds_audio_buffer audio = GetAudioBuffer(path, DS_GetModelSampleRate(context));

  // Pass audio to DeepSpeech
  // We take half of buffer_size because buffer is a char* while
  // LocalDsSTT() expected a short*
  ds_result result = LocalDsSTT(context,
                                (const short*)audio.buffer,
                                audio.buffer_size / 2,
                                extended_metadata,
                                json_output);
  free(audio.buffer);

  if (result.string) {
    LOG("%s\n", result.string);
    DS_FreeString((char*)result.string);
  }

  if (show_times) {
    LOG("cpu_time_overall=%.05f\n",
           result.cpu_time_overall);
  }
}

#if 0
std::vector<std::string>
SplitStringOnDelim(std::string in_string, std::string delim)
{
  std::vector<std::string> out_vector;
  char * tmp_str = new char[in_string.size() + 1];
  std::copy(in_string.begin(), in_string.end(), tmp_str);
  tmp_str[in_string.size()] = '\0';
  const char* token = strtok(tmp_str, delim.c_str());
  while( token != NULL ) {
    out_vector.push_back(token);
    token = strtok(NULL, delim.c_str());
  }
  delete[] tmp_str;
  return out_vector;
}
#endif


#ifdef AUTYPER_APP
int audio2text(int argc, char **argv)
#else
int main(int argc, char **argv)
#endif
{
  char* model = NULL;
  char* scorer = NULL;
  char* audio = NULL;
  
  int i = 1;
  
  while (i < argc) {
    if ( strcmp(argv[i], "--model") == 0) {
      i++;
      if (i >= argc) {
        LOG("missing arg for model\n");
        return 1;
      }
      model = argv[i];
    }
    if ( strcmp(argv[i], "--scorer") == 0) {
      i++;
      if (i >= argc) {
        LOG("missing arg for scorer\n");
        return 1;
      }
      scorer = argv[i];
    }
    if ( strcmp(argv[i], "--audio") == 0) {
      i++;
      if (i >= argc) {
        LOG("missing arg for audio\n");
        return 1;
      }
      audio = argv[i];
    }
    i++;
  }

  if ( ! model ) { LOG("model must be provided\n"); return 1; }
  //if ( ! scorer ) { LOG("scorer must be provided\n"); return 1; }
  if ( ! audio ) { LOG("audio must be provided\n"); return 1; }
  LOG("Initialise DeepSpeech Client\n");

  // Initialise DeepSpeech
  ModelState* ctx;
  // sphinx-doc: c_ref_model_start
  int status = DS_CreateModel(model, &ctx);
  if (status != 0) {
    char* error = DS_ErrorCodeToErrorMessage(status);
    LOG_E("Could not create model: %s\n", error);
    free(error);
    return 1;
  }

#if 1
  if (set_beamwidth) {
    status = DS_SetModelBeamWidth(ctx, beam_width);
    if (status != 0) {
      LOG_E("Could not set model beam width.\n");
      return 1;
    }
  }
#endif

  if (scorer) {
    status = DS_EnableExternalScorer(ctx, scorer);
    if (status != 0) {
      LOG_E("Could not enable external scorer.\n");
      return 1;
    }
    if (set_alphabeta) {
      status = DS_SetScorerAlphaBeta(ctx, lm_alpha, lm_beta);
      if (status != 0) {
        LOG_E("Error setting scorer alpha and beta.\n");
        return 1;
      }
    }
  }
  // sphinx-doc: c_ref_model_stop

#if 0
  if (hot_words) {
    std::vector<std::string> hot_words_ = SplitStringOnDelim(hot_words, ",");
    for ( std::string hot_word_ : hot_words_ ) {
      std::vector<std::string> pair_ = SplitStringOnDelim(hot_word_, ":");
      const char* word = (pair_[0]).c_str();
      // the strtof function will return 0 in case of non numeric characters
      // so, check the boost string before we turn it into a float
      bool boost_is_valid = (pair_[1].find_first_not_of("-.0123456789") == std::string::npos);
      float boost = strtof((pair_[1]).c_str(),0);
      status = DS_AddHotWord(ctx, word, boost);
      if (status != 0 || !boost_is_valid) {
        LOG_E("Could not enable hot-word.\n");
        return 1;
      }
    }
  }
#endif


#ifndef NO_SOX
  // Initialise SOX
  assert(sox_init() == SOX_SUCCESS);
#endif

  struct stat wav_info;
  if (0 != stat(audio, &wav_info)) {
    LOG("Error on stat: %d\n", errno);
  }

  switch (wav_info.st_mode & S_IFMT) {
#ifndef _MSC_VER
    case S_IFLNK:
#endif
    case S_IFREG:
        ProcessFile(ctx, audio, show_times);
      break;

#ifndef NO_DIR
    case S_IFDIR:
        {
          LOG("Running on directory %s\n", audio);
          DIR* wav_dir = opendir(audio);
          assert(wav_dir);

          struct dirent* entry;
          while ((entry = readdir(wav_dir)) != NULL) {
            std::string fname = std::string(entry->d_name);
            if (fname.find(".wav") == std::string::npos) {
              continue;
            }

            std::ostringstream fullpath;
            fullpath << audio << "/" << fname;
            std::string path = fullpath.str();
            LOG("> %s\n", path.c_str());
            ProcessFile(ctx, path.c_str(), show_times);
          }
          closedir(wav_dir);
        }
      break;
#endif

    default:
        LOG("Unexpected type for %s: %d\n", audio, (wav_info.st_mode & S_IFMT));
      break;
  }

#ifndef NO_SOX
  // Deinitialise and quit
  sox_quit();
#endif // NO_SOX

  DS_FreeModel(ctx);

  return 0;
}
#endif
