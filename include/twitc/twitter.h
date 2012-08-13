/*
 * libtwitc - C Support Library for Twitter
 * Copyright (C) 2012 Orazio Briante orazio.briante@hotmail.it
 *                    Patryk Rzucidlo ptkdev@gmail.com
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

#ifndef TWITTER_H_
#define TWITTER_H_

#include <twitc/stdredef.h>
#include <twitc/user.h>
#include <twitc/timeline.h>


typedef struct {
	string_t  authorize_url;
	string_t  request_url;
	string_t  tokenaccess_url;

	string_t  status_url;
	string_t  home_timeline_url;
	string_t  public_timeline_url;
	string_t  mentions_timeline_url;
	string_t  friends_timeline_url;
	string_t  user_timeline_url;
	string_t  rt_by_me_timeline_url;
	string_t  rt_to_me_timeline_url;
	string_t  rt_of_me_timeline_url;
}twitterURLS_t;


extern	twitterURLS_t	*initURLS			(const string_t, const string_t);

extern	string_t		tokenTemp			(const twitterURLS_t *, const string_t, const string_t );
extern	string_t		tokenTempBrowser	(const twitterURLS_t *, const string_t , const string_t );
extern	user_t			*tokenAccess		(const twitterURLS_t *, const string_t , const string_t );
extern	string_t		tokenRequest		(const twitterURLS_t *, const string_t , const string_t );

extern	byte_t			sendTweet			(const twitterURLS_t *, const user_t * user_t, const string_t);
extern	string_t		getTimeline			(const string_t timelineURL, const user_t* user );


#endif /* TWITTER_H_ */
