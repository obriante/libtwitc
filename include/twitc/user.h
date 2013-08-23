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

#ifndef USER_H_
#define USER_H_

#include <twitc/stdredef.h>

#define		MY_ENCODING		"ISO-8859-1"

typedef struct{
	string_t id;
	string_t screenName;
	string_t token;
	string_t secretToken;
	string_t consumerKey;
	string_t consumerSecretKey;
}user_t;

extern	user_t 			*initUser	(const string_t, const string_t, const string_t, const string_t, const string_t, const string_t);
extern	void			writeUserFile	(const user_t *, const string_t);
extern	user_t			*readUserFile	(const string_t);
extern	void			uninitUser	(user_t *);

#endif /* USER_H_ */
