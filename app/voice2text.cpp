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

#include "voice2text.h"
#include "log.h"
#include <stdio.h>

#include "deepspeech.h"

#ifdef _MACOS
  #include <malloc/malloc.h>
#else
  #include <malloc.h>
#endif


#define MODEL "..\\..\\autyper\\deepspeech\\models\\deepspeech-0.9.2-models.pbmm"
#define SCORER "..\\..\\autyper\\deepspeech\\models\\deepspeech-0.9.2-models.scorer"

Voice2Text::Voice2Text(): decoder(NULL)
{

}



void Voice2Text::run (void)
{
  const char * txt;
  QString result_txt("Hello");
  /* ... here is the expensive or blocking operation ... */
  ModelState* ctx;
  // sphinx-doc: c_ref_model_start
  int status = DS_CreateModel(MODEL, &ctx);
  if (status != 0) {
    char* error = DS_ErrorCodeToErrorMessage(status);
    LOG_E("Could not create model: %s\n", error);
    free(error);
    CResult * res = new CResult(ERROR_BAD_MODEL_FILE, QString("Could not create Model") );
    emit resultReady(res);
    return;
  }

  status = DS_EnableExternalScorer(ctx, SCORER);
  if (status != 0) {
    LOG_E("Could not enable external scorer.\n");
    CResult * res = new CResult(ERROR_BAD_SCORER_FILE, QString("Could not create Model") );
    emit resultReady(res);
    return;
  }

  StreamingState* stream_st_ctx;
  status = DS_CreateStream(ctx, &stream_st_ctx);
  if (status != DS_ERR_OK) {
    LOG_E("DS_CreateStream: error = %d", status);
    CResult * res = new CResult(ERROR_BAD_SCORER_FILE, QString("Could not create Model") );
    emit resultReady(res);
    return;
  }

  size_t off = 0;
  const char *last = nullptr;
  const char *prev = nullptr;
  uint32_t nsamples, progress;
  while (1) {
    feeder->getSamples(aBuffer, AUDIO_BUFFER_NUM_SAMPLES, &nsamples, &progress);
    if (nsamples == 0) {
      txt = DS_FinishStream(stream_st_ctx);
      LOG_E("DS_CreateStream: error = %d", status);
      CResult * res = new CResult(FINAL_TEXT, QString(txt) );
      DS_FreeString((char *) txt);
      emit resultReady(res);
      break;
    }

    DS_FeedAudioContent(stream_st_ctx, aBuffer, nsamples);
    const char* partial = DS_IntermediateDecode(stream_st_ctx);
    CResult * res = new CResult(PARTIAL_TEXT, QString(partial) );
    DS_FreeString((char *) partial);
    emit resultReady(res);
  }

#if 0
  size_t aBufferSize;
  while (off < aBufferSize) {
    size_t cur = aBufferSize - off > stream_size ? stream_size : aBufferSize - off;
    DS_FeedAudioContent(stream_st_ctx, aBuffer + off, cur);
    off += cur;
    prev = last;
    const char* partial = DS_IntermediateDecode(stream_st_ctx);
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
  res.string = DS_FinishStream(stream_st_ctx);


  //CResult * res = new CResult(FINAL_TEXT, QString("All done!") );
  //emit resultReady(res);
#endif

}

Voice2Text::Voice2Text( QString filename, void * handler_func, void * handler_ctx)
{

}

Voice2Text::Voice2Text( QString filename, FeederBase * _feeder)
{
  this->filename = filename;
  feeder =_feeder;
}

void cppProtocolInit(void)
{
}

