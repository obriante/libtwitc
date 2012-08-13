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

#ifndef STDREDEF_H_
#define STDREDEF_H_

#ifdef __cplusplus
extern "C"
{  /* only need to export C interface if used by C++ source code#endif */
#endif

typedef	 unsigned	char			byte_t;
typedef	 unsigned	short			word_t;
typedef	 unsigned	long			dword_t;
typedef				void*			voidPtr_t;
typedef				char*			string_t;
typedef				struct timeval	timeval_t;
typedef				struct termios	termios_t;
typedef 			struct tm		tm_t;
typedef				struct passwd	passwd_t;


#ifdef __cplusplus
}
#endif

#endif /* STDREDEF_H_ */
