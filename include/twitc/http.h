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

#ifndef HTTP_H_
#define HTTP_H_

/* URL separators */
#define URL_SEP_AMP						"&"
#define URL_SEP_QUES					"?"
#define EXTENSIONFORMAT_XML				".xml"

#define PROTOCOL_HTTP					"http://"
#define PROTOCOL_HTTPS					"https://"

#include <twitc/twitter.h>

extern byte_t
getFileCURL(string_t, string_t);
extern string_t
getPageCURL(string_t);

extern string_t
componeOAUTH_URL(const twitterURLS_t *, const ProtocolType_t, const string_t,
    ApiFormatType_t);
extern string_t
componeAPI_URL(const twitterURLS_t *, const ProtocolType_t, const string_t,
    ApiFormatType_t);
#endif /* HTTP_H_ */
