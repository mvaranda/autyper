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
#include <QString>

#ifdef _MACOS
  #include <malloc/malloc.h>
#else
  #include <malloc.h>
#endif

Voice2Text::Voice2Text()
{

}

void Voice2Text::abortRequest(void)
{
  abort = true;
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

#define   AUDIO_BUFFER_SPLIT_START ((AUDIO_BUFFER_NUM_SAMPLES / 3) * 2) // about after 4 seconds
#define   SILENCE_WINDOW_IN_SAMPLES (1280) // about 80milliseconds

uint32_t Voice2Text::scanForSilence(void) // actually the lower power window.
{
  int i,p;

  // TODO: consider if we need to apply a hamming window to avoid missleadings due high power at the window edges.
  // however, if that is the case, the computation will be very "expensive" for detecting low power splitting points.

  uint64_t power = 0;
  uint64_t lowest_power = ~0;  // set it to max power value (complement of 0 -> 0xffff...)
  uint32_t cnt=0, lowest_power_idx = AUDIO_BUFFER_SPLIT_START;

  // first window power:
  //   for best optimazation we will slide the window... so we only add all power once.
  //   then we will later (in the scann loop) remove the first sample and add the last to slide the windows
  for (i = AUDIO_BUFFER_SPLIT_START; i < AUDIO_BUFFER_SPLIT_START + SILENCE_WINDOW_IN_SAMPLES; i++) {
    power += aBuffer[i] * aBuffer[i]; // square the sample to get its power
    cnt++;
  }
  LOG("cnt = %d\n", cnt);

  // scan
  for (i = AUDIO_BUFFER_SPLIT_START + 1; i < (AUDIO_BUFFER_NUM_SAMPLES - SILENCE_WINDOW_IN_SAMPLES); i++) {
    // slide window by removing the first sample
    power -= aBuffer[i-1] * aBuffer[i-1];
    // and adding last sample
    power += aBuffer[i + SILENCE_WINDOW_IN_SAMPLES - 1] * aBuffer[i + SILENCE_WINDOW_IN_SAMPLES - 1];

    if (lowest_power > power) {
      lowest_power = power;
      lowest_power_idx = i;
    }
  }
  lowest_power_idx = lowest_power_idx + (SILENCE_WINDOW_IN_SAMPLES / 2); //get center of the window
  if (lowest_power_idx >= (AUDIO_BUFFER_NUM_SAMPLES - 1))
    lowest_power_idx = (AUDIO_BUFFER_NUM_SAMPLES - 1);
  return lowest_power_idx;
}


void Voice2Text::run (void)
{
  const char * txt;
  uint32_t i, silence_idx = 0;
  int status;

  if (model_ctx == NULL) {
    status = DS_CreateModel(model_fn.toStdString().c_str(), &model_ctx);
    if (status != 0) {
      char* error = DS_ErrorCodeToErrorMessage(status);
      LOG_E("Could not create model: %s\n", error);
      DS_FreeString((char *) error);
      CResult * res = new CResult(ERROR_BAD_MODEL_FILE, QString("Could not create Model"), 0 );
      emit resultReady(res);
      return;
    }

    status = DS_EnableExternalScorer(model_ctx, scorer_fn.toStdString().c_str());
    if (status != 0) {
      char* error = DS_ErrorCodeToErrorMessage(status);
      LOG_E("Could not create scorer: %s\n", error);
      DS_FreeString((char *) error);
      LOG_E("Could not enable external scorer.\n");
      CResult * res = new CResult(ERROR_BAD_SCORER_FILE, QString("Could not create Model"), 0 );
      emit resultReady(res);

      return;
    }
  }

  uint32_t fromfeeder, progress, left_over_samples = 0;


  while (1) {
    if (abort) {
      delete feeder;
      CResult * res = new CResult(ABORT_TEXT, QString("conversion Aborted"), 0 );
      emit resultReady(res);
      break;
    }

    feeder->getSamples(&aBuffer[left_over_samples], AUDIO_BUFFER_NUM_SAMPLES - left_over_samples, &fromfeeder, &progress);
    if ((fromfeeder +  left_over_samples) < AUDIO_BUFFER_NUM_SAMPLES) { // last block
      txt = DS_SpeechToText(model_ctx, aBuffer, fromfeeder +  left_over_samples);
      CResult * res = new CResult(FINAL_TEXT, QString(txt), progress );
      DS_FreeString((char *) txt);
      emit resultReady(res);
      break;
    }

    silence_idx = scanForSilence();
    LOG("Split at: %d\n", silence_idx);

    txt = DS_SpeechToText(model_ctx, aBuffer, silence_idx);
    CResult * res = new CResult(PARTIAL_TEXT, QString(txt), progress );
    DS_FreeString((char *) txt);
    emit resultReady(res);

    // move left over to the begining
    for (i=0; i < AUDIO_BUFFER_NUM_SAMPLES -  silence_idx; i++) {
      aBuffer[i] = aBuffer[i + silence_idx];
    }
    left_over_samples = AUDIO_BUFFER_NUM_SAMPLES -  silence_idx;

  }

  quit();
}


Voice2Text::Voice2Text( QString filename, QString model, QString scorer, FeederBase * _feeder)
{
  this->filename = filename;
  model_fn = model;
  scorer_fn = scorer;
  feeder =_feeder;
  model_ctx = NULL;
}

void cppProtocolInit(void)
{
}

