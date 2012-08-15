/*
 * Copyright © 2012 - Orazio Briante <orazio.briante@hotmail.it>
 *
 * Licensed under the GNU Lesser General Public License Version 3
 *
 * This program is free software  you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation  either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY  without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 * or write to the Free Software Foundation, Inc., 51 Franklin St
 * Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef TWITTER_H_
#define TWITTER_H_

#define TWITTER_COLON					":"
#define  TWITTER_EOS					'\0'
#define  MAX_TIMELINE_TWEET_COUNT			200

/* Miscellaneous data used to build twitter URLs*/
#define TWITTER_STATUSSTRING				"status "
#define TWITTER_TEXTSTRING				"text "
#define TWITTER_QUERYSTRING				"query "
#define TWITTER_SEARCHQUERYSTRING			"q "
#define TWITTER_SCREENNAME				"screen_name "
#define TWITTER_USERID					"user_id "
#define TWITTER_EXTENSIONFORMAT_XML			".xml"
#define TWITTER_EXTENSIONFORMAT_JSON			".json"
#define TWITTER_PROTOCOL_HTTP				"http://"
#define TWITTER_PROTOCOL_HTTPS				"https://"
#define TWITTER_TARGETSCREENNAME			"target_screen_name "
#define TWITTER_TARGETUSERID				"target_id "
#define TWITTER_SINCEID					"since_id "
#define TWITTER_TRIMUSER				"trim_user true"
#define TWITTER_INCRETWEETS				"include_rts true"
#define TWITTER_COUNT					"count "

/* URL separators */
#define TWITTER_URL_SEP_AMP				"&"
#define TWITTER_URL_SEP_QUES				"?"


/* Search URLs */
#define TWITTER_SEARCH_URL				"search.twitter.com/search"

/* Status URLs */
#define TWITTER_STATUSUPDATE_URL			"api.twitter.com/1/statuses/update"
#define TWITTER_STATUSSHOW_URL				"api.twitter.com/1/statuses/show/"
#define TWITTER_STATUDESTROY_URL			"api.twitter.com/1/statuses/destroy/"

/* Timeline URLs */
#define TWITTER_HOME_TIMELINE_URL			"api.twitter.com/1/statuses/home_timeline"
#define TWITTER_PUBLIC_TIMELINE_URL			"api.twitter.com/1/statuses/public_timeline"
#define TWITTER_FEATURED_USERS_URL			"api.twitter.com/1/statuses/featured"
#define TWITTER_FRIENDS_TIMELINE_URL			"api.twitter.com/1/statuses/friends_timeline"
#define TWITTER_MENTIONS_URL				"api.twitter.com/1/statuses/mentions"
#define TWITTER_USERTIMELINE_URL			"api.twitter.com/1/statuses/user_timeline"

/* Users URLs */
#define TWITTER_SHOWUSERS_URL				"api.twitter.com/1/users/show"
#define TWITTER_SHOWFRIENDS_URL				"api.twitter.com/1/statuses/friends"
#define TWITTER_SHOWFOLLOWERS_URL			"api.twitter.com/1/statuses/followers"

/* Direct messages URLs */
#define TWITTER_DIRECTMESSAGES_URL			"api.twitter.com/1/direct_messages"
#define TWITTER_DIRECTMESSAGENEW_URL			"api.twitter.com/1/direct_messages/new"
#define TWITTER_DIRECTMESSAGESSENT_URL			"api.twitter.com/1/direct_messages/sent"
#define TWITTER_DIRECTMESSAGEDESTROY_URL		"api.twitter.com/1/direct_messages/destroy/"

/* Friendships URLs */
#define TWITTER_FRIENDSHIPSCREATE_URL			"api.twitter.com/1/friendships/create"
#define TWITTER_FRIENDSHIPSDESTROY_URL			"api.twitter.com/1/friendships/destroy"
#define TWITTER_FRIENDSHIPSSHOW_URL			"api.twitter.com/1/friendships/show"

/* Social graphs URLs */
#define TWITTER_FRIENDSIDS_URL				"api.twitter.com/1/friends/ids"
#define TWITTER_FOLLOWERSIDS_URL			"api.twitter.com/1/followers/ids"

/* Account URLs */
#define TWITTER_ACCOUNTRATELIMIT_URL			"api.twitter.com/1/account/rate_limit_status"
#define TWITTER_ACCOUNTVERIFYCRED_URL			"api.twitter.com/1/account/verify_credentials"

/* Favorites URLs */
#define TWITTER_FAVORITESGET_URL			"api.twitter.com/1/favorites"
#define TWITTER_FAVORITECREATE_URL			"api.twitter.com/1/favorites/create/"
#define TWITTER_FAVORITEDESTROY_URL			"api.twitter.com/1/favorites/destroy/"

/* Block URLs */
#define TWITTER_BLOCKSCREATE_URL			"api.twitter.com/1/blocks/create/"
#define TWITTER_BLOCKSDESTROY_URL			"api.twitter.com/1/blocks/destroy/"

/* Saved Search URLs */
#define TWITTER_SAVEDSEARCHGET_URL			"api.twitter.com/1/saved_searches"
#define TWITTER_SAVEDSEARCHSHOW_URL			"api.twitter.com/1/saved_searches/show/"
#define TWITTER_SAVEDSEARCHCREATE_URL			"api.twitter.com/1/saved_searches/create"
#define TWITTER_SAVEDSEARCHDESTROY_URL			"api.twitter.com/1/saved_searches/destroy/"

/* Trends URLs */
#define TWITTER_TRENDS_URL				"api.twitter.com/1/trends"
#define TWITTER_TRENDSDAILY_URL				"api.twitter.com/1/trends/daily"
#define TWITTER_TRENDSCURRENT_URL			"api.twitter.com/1/trends/current"
#define TWITTER_TRENDSWEEKLY_URL			"api.twitter.com/1/trends/weekly"
#define TWITTER_TRENDSAVAILABLE_URL			"api.twitter.com/1/trends/available"

#endif /* TWITTER_H_ */
