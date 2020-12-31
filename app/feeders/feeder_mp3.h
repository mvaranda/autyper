#ifndef FEEDERMP3_H
#define FEEDERMP3_H
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

class FeederMp3: FeederBase
{
public:
  FeederMp3(QString input, uint32_t model_samplerate);
  //feeder_res_t getSamples(sample_t * samples, uint32_t num_req_samples, uint32_t * num_deliver_samples, uint32_t * progress);

private:
  FeederMp3() {};

};

#endif // FEEDERMP3_H
