#ifndef LOG_H
#define LOG_H

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
#include <QDebug>
#if 1
#define LOG         qDebug
#define LOG_E       qDebug
#define LOG_I       qDebug
#define LOG_W       qDebug
#else
#define LOG         printf
#define LOG_E       printf
#define LOG_I       printf
#define LOG_W       printf
#endif


#ifdef __cplusplus
  extern "C" {
#endif


  void qDebugC(char * format,...);


#ifdef __cplusplus
}
#endif




#endif // LOG_H
