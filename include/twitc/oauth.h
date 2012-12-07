/*
 * Copyright © 2012 - Orazio Briante <orazio.briante@hotmail.it>
 * Patryk Rzucidlo <ptkdev@gmail.com>
 * Alfredo Liguoro  <freddy@haxaddicts.net>
 *
 * Licensed under the GNU Lesser General Public License Version 3
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 * or write to the Free Software Foundation, Inc., 51 Franklin St
 * Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OAUTH_H_
#define OAUTH_H_

#include <twitc/stdredef.h>
#include <twitc/twitter.h>
#include <twitc/user.h>


extern	string_t
tokenRequest		(const twitterURLS_t *,
		const string_t c_key,
		const string_t);

extern	string_t
tokenTemp			(const twitterURLS_t *,
		const string_t,
		const string_t);

extern	string_t
tokenTempBrowser	(const twitterURLS_t *,
		const string_t,
		const string_t);

extern	user_t
*tokenAccess		(const twitterURLS_t *,
		const string_t,
		const string_t );


#endif /* OAUTH_H_ */
