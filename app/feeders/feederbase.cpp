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

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "feederbase.h"
#include "log.h"


FeederBase::FeederBase(QString input_name)
{
  input = input_name;
}

feeder_t FeederBase::getType(void)
{
  return feeder_type;
}

QString FeederBase::getInputName(void)
{
  return input;
}

//====================== Resample =======================
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
Destination samples: D0        D1        D2        D3        D4        T5
                     |         |         |         |         |         |
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

extern "C" {
static sample_t      bufin[RESAMPLE_NUM_SAMPLES]; // for resample


int resample( const char * filename, unsigned int samplerate_in,
              const char * file_out, unsigned int samplerate_out)
{
  double St = 1.0 / samplerate_in;

  double i = 0.0;
  double T = 0.0;
  double Dp = 1.0 / samplerate_out; // destination period
  sample_t         V, Vn, Vd, VD2;

  unsigned int samples_available_space = RESAMPLE_NUM_SAMPLES;

#if 0 // reject lower input samplerate
  if (samplerate_out >= samplerate_in) {
    LOG("resample: output sample rate %d must be lower than input's %d.\n", samplerate_out, samplerate_in);
    return 1;
  }
#endif

  unsigned int nread, nsamples, nsamples_moved = 0;
  double integer;

  FILE * fh = fopen(filename, "rb");
  if (! fh) {
    LOG("resample: Could not open input file: \"%s\"\n", filename);
    return 1;
  }

  FILE * f_out = fopen(file_out, "wb");
  if (! f_out) {
    LOG("resample: Could not open output file: \"%s\"\n", file_out);
    return 1;
  }

  while ( (nread = fread( &bufin[RESAMPLE_NUM_SAMPLES - samples_available_space], 1, samples_available_space * sizeof(sample_t), fh) ) > 0) {
    nsamples = nsamples_moved + nread/sizeof(sample_t);
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
      if ( (integer >= RESAMPLE_NUM_SAMPLES) || (integer >= nsamples) ) {
        LOG("Before sample not available\n");
        samples_available_space = RESAMPLE_NUM_SAMPLES;
        nsamples_moved = 0;
        T -= St * nsamples;
        while (T < 0) {
          LOG("*** T negative\n");
          T += Dp;
        }
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
        nsamples_moved = 1;
        samples_available_space = RESAMPLE_NUM_SAMPLES - 1;
        T -= St * (nsamples - 1);
        while (T < 0) {
          LOG("*** T negative\n");
          T += Dp;
        }
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

      T += Dp;
    }

    //LOG("new block\n");


  }
  fclose(fh);
  fclose(f_out);

  return 0;
}

} // for extern "C" {

