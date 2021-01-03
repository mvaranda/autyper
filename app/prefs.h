#ifndef PREFS_H
#define PREFS_H

/*
 * This file is part of the AuTyper distribution (https://github.com/mvaranda/autyper).
 * Copyright (c) 2020 Varanda Labs Inc.
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

#include <QString>

class Prefs
{
public:
  Prefs();
  static void load(void);
  static void save(void);

  static QString info_url;
  static QString active_model_file;
  static QString active_scorer_file;
  static QString user_path; // for text
  static QString user_audio_path;
  static QString user_model_path;

};

#endif // PREFS_H
