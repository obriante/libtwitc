/*
 * libtwitc - C Support Library for Twitter
 * Copyright (C) 2012 Orazio Briante orazio.briante@hotmail.it
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <twitc/stdredef.h>
#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#  define debug(template, ...)	_debug(__FUNCTION__, template, ## __VA_ARGS__)
#else
#  define debug(template, ...)
#endif

#define info(template, ...)		_info (__FUNCTION__, template, ## __VA_ARGS__)
#define warning(template, ...)	_warning(__FUNCTION__, template, ## __VA_ARGS__)
#define error(template, ...)	_error(__FUNCTION__, template, ## __VA_ARGS__)

typedef enum
{
high,
medium,
low
}LogLevel;

static FILE *logFile=NULL;
static LogLevel logLevel=low;


extern	void	initLog		(const string_t, const LogLevel, const long);
extern	void	uninitLog	(	);

extern	void	_warning	(const char * , const char *, ...);
extern	void	_info		(const char * , const char *, ...);
extern	void	_error		(const char * , const char *, ...);
extern	void	_debug		(const char * , const char *, ...);

#endif /* _DEBUG_H_ */
