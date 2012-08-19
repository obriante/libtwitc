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

#define  MAX_TIMELINE_TWEET_COUNT	200

/* Miscellaneous data used to build twitter URLs*/
#define STATUSSTRING				"status "
#define TEXTSTRING					"text "
#define QUERYSTRING					"query "
#define SEARCHQUERYSTRING			"q "
#define SCREENNAME					"screen_name "
#define USERID						"user_id "

#define TARGETSCREENNAME			"target_screen_name "
#define TARGETUSERID				"target_id "
#define SINCEID						"since_id "
#define TRIMUSER					"trim_user true"
#define INCRETWEETS					"include_rts true"
#define COUNT						"count "

/* default url*/

#define OAUTH_URL_DEFAULT			"api.twitter.com/oauth/"
#define API_URL_DEFAULT				"api.twitter.com/1/"
#define SEARCH_URL_DEFAULT			"search.twitter.com/search"

/* OAUTH URL */
#define REQTOKEN_URL				"request_token"
#define AUTHORIZE_URL				"authorize"
#define ACCESS_TOKEN_URL			"access_token"

/* Search URLs */

/* Status URLs */
#define STATUSUPDATE_URL			"statuses/update"
#define STATUSSHOW_URL				"statuses/show/"
#define STATUDESTROY_URL			"statuses/destroy/"

/* Timeline URLs */
#define HOME_TIMELINE_URL			"statuses/home_timeline"
#define PUBLIC_TIMELINE_URL			"statuses/public_timeline"
#define FEATURED_USERS_URL			"statuses/featured"
#define FRIENDS_TIMELINE_URL		"statuses/friends_timeline"
#define MENTIONS_URL				"statuses/mentions"
#define USERTIMELINE_URL			"statuses/user_timeline"

/* Users URLs */
#define SHOWUSERS_URL				"users/show"
#define SHOWFRIENDS_URL				"statuses/friends"
#define SHOWFOLLOWERS_URL			"statuses/followers"

/* Direct messages URLs */
#define DIRECTMESSAGES_URL			"direct_messages"
#define DIRECTMESSAGENEW_URL		"direct_messages/new"
#define DIRECTMESSAGESSENT_URL		"direct_messages/sent"
#define DIRECTMESSAGEDESTROY_URL	"direct_messages/destroy/"

/* Friendships URLs */
#define FRIENDSHIPSCREATE_URL		"friendships/create"
#define FRIENDSHIPSDESTROY_URL		"friendships/destroy"
#define FRIENDSHIPSSHOW_URL			"friendships/show"

/* Social graphs URLs */
#define FRIENDSIDS_URL				"friends/ids"
#define FOLLOWERSIDS_URL			"followers/ids"

/* Account URLs */
#define ACCOUNTRATELIMIT_URL		"account/rate_limit_status"
#define ACCOUNTVERIFYCRED_URL		"account/verify_credentials"

/* Favorites URLs */
#define FAVORITESGET_URL			"favorites"
#define FAVORITECREATE_URL			"favorites/create/"
#define FAVORITEDESTROY_URL			"favorites/destroy/"

/* Block URLs */
#define BLOCKSCREATE_URL			"blocks/create/"
#define BLOCKSDESTROY_URL			"blocks/destroy/"

/* Saved Search URLs */
#define SAVEDSEARCHGET_URL			"saved_searches"
#define SAVEDSEARCHSHOW_URL			"saved_searches/show/"
#define SAVEDSEARCHCREATE_URL		"saved_searches/create"
#define SAVEDSEARCHDESTROY_URL		"saved_searches/destroy/"

/* Trends URLs */
#define TRENDS_URL					"trends"
#define TRENDSDAILY_URL				"trends/daily"
#define TRENDSCURRENT_URL			"trends/current"
#define TRENDSWEEKLY_URL			"trends/weekly"
#define TRENDSAVAILABLE_URL			"trends/available"

typedef enum
{
  Xml, None
} ApiFormatType_t;

typedef enum
{
  Http, Https
} ProtocolType_t;

typedef enum
{
  GET, POST
} methodType_t;

typedef struct
{
  string_t oauth_URL;
  string_t api_URL;
  string_t serch_URL;
} twitterURLS_t;

extern twitterURLS_t *
initURLS(const string_t, const string_t, const string_t);
extern void
uninitURLS(twitterURLS_t *);

#endif /* TWITTER_H_ */
