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

// for printf like (char *)
#define LOG         qDebug
#define LOG_E       qCritical
#define LOG_I       qInfo
#define LOG_W       qWarning

// for QString content
#define LOGS(s)     qDebug(s.toStdString().c_str())
#define LOGS_E(s)   qCritical(s.toStdString().c_str())
#define LOGS_I(s)   qInfo(s.toStdString().c_str())
#define LOGS_W(s)   qWarning(s.toStdString().c_str())

#ifdef __cplusplus
  extern "C" {
#endif

  void qDebugC(char * format,...);


#ifdef __cplusplus
}
#endif




#endif // LOG_H
