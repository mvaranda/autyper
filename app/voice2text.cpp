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

Voice2Text::Voice2Text(): decoder(NULL)
{

}

uint32_t Voice2Text::getModelSampleRate (QString filaname)
{
  uint32_t ret = 0;
  ModelState* ctx = NULL;
  // sphinx-doc: c_ref_model_start
  int status = DS_CreateModel(filaname.toStdString().c_str(), &ctx);
  if (status == 0) {
    ret = DS_GetModelSampleRate(ctx);
  }
  else {
    char* error = DS_ErrorCodeToErrorMessage(status);
    LOG_E("Could not create model: %s\n", error);
  }
  if (ctx) {
    DS_FreeModel(ctx);
  }
  return ret;
}


void Voice2Text::run (void)
{
  const char * txt;
 // QString result_txt("Hello");

  LOG("HERE 1");

  /* ... here is the expensive or blocking operation ... */
  ModelState* ctx;
  // sphinx-doc: c_ref_model_start
  int status = DS_CreateModel(model_fn.toStdString().c_str(), &ctx);
  if (status != 0) {
    char* error = DS_ErrorCodeToErrorMessage(status);
    LOG_E("Could not create model: %s\n", error);
    DS_FreeString((char *) error);
    CResult * res = new CResult(ERROR_BAD_MODEL_FILE, QString("Could not create Model") );
    emit resultReady(res);
    return;
  }

    LOG("HERE 2");

  status = DS_EnableExternalScorer(ctx, scorer_fn.toStdString().c_str());
  if (status != 0) {
    char* error = DS_ErrorCodeToErrorMessage(status);
    LOG_E("Could not create scorer: %s\n", error);
    DS_FreeString((char *) error);
    LOG_E("Could not enable external scorer.\n");
    CResult * res = new CResult(ERROR_BAD_SCORER_FILE, QString("Could not create Model") );
    emit resultReady(res);

    return;
  }

  StreamingState* stream_st_ctx;
  status = DS_CreateStream(ctx, &stream_st_ctx);
  if (status != DS_ERR_OK) {
    LOG_E("DS_CreateStream: error = %d", status);
    CResult * res = new CResult(ERROR_BAD_SCORER_FILE, QString("Could not create DS stream") );
    emit resultReady(res);
    return;
  }

  uint32_t nsamples, progress;

    LOG("HERE 3");

  while (1) {
    feeder->getSamples(aBuffer, AUDIO_BUFFER_NUM_SAMPLES, &nsamples, &progress);
    if (nsamples == 0) {
      txt = DS_FinishStream(stream_st_ctx);
      CResult * res = new CResult(FINAL_TEXT, QString(txt) );
      DS_FreeString((char *) txt);
      emit resultReady(res);
      break;
    }

  LOG("HERE 4");
    DS_FeedAudioContent(stream_st_ctx, aBuffer, nsamples);
    const char* partial = DS_IntermediateDecode(stream_st_ctx);
    CResult * res = new CResult(PARTIAL_TEXT, QString(partial) );
    DS_FreeString((char *) partial);
    emit resultReady(res);
  }

  quit();
}

Voice2Text::Voice2Text( QString filename, void * handler_func, void * handler_ctx)
{

}

Voice2Text::Voice2Text( QString filename, QString model, QString scorer, FeederBase * _feeder)
{
  this->filename = filename;
  model_fn = model;
  scorer_fn = scorer;
  feeder =_feeder;
}

void cppProtocolInit(void)
{
}

