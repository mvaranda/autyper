#ifndef C_UTILS_H
#define C_UTILS_H
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

#define MAX_FILE_SIZE                   (1024 * 1024 * 10) // 10 Mbytes
#define FILE_RAW_FROM_MP3               "\\samples.$$$"
#define FILE_RAW_FROM_RESAMPLER         "\\samples.raw"
#define DEEPSPEECH_SAMPLERATE           16000

typedef short sample_t;

#define RESAMPLE_NUM_SAMPLES (1024 * 2)

#ifdef __cplusplus
extern "C" {
#endif

unsigned int getMp3SampleRate( void );
FILE * convertMp3ToRaw(const char * mp3file, const char * path);
int resample( const char * filename, unsigned int samplerate_in,
              const char * file_out, unsigned int samplerate_out);














#ifdef __cplusplus
  }
#endif


#endif // C_UTILS_H
