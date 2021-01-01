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

#include "feederbase.h"
#include "log.h"


FeederBase::FeederBase(QString input_name, uint32_t model_samplerate)
{
  input = input_name;
  modelSamplerate = model_samplerate;
  total_read = 0;
}

FeederBase::~FeederBase()
{
  if (samples_fh)
    fclose(samples_fh);
}

feeder_t FeederBase::getType(void)
{
  return feeder_type;
}

QString FeederBase::getInputName(void)
{
  return input;
}

feeder_res_t FeederBase::getSamples(sample_t * samples, uint32_t num_req_samples, uint32_t * num_deliver_samples, uint32_t * progress)
{
  int nread = fread(samples, 1, num_req_samples * 2, samples_fh);
  total_read += nread;
  *num_deliver_samples = nread / 2;
  *progress = (total_read * 100) / samples_file_size;

}


