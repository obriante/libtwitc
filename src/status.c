/*
 * Copyright © 2012 - Orazio Briante <orazio.briante@hotmail.it>
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

#include <twitc/http.h>
#include <twitc/status.h>
#include <twitc/user.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <oauth.h>
#include <libxml/xmlreader.h>
#include <json.h>


#ifdef __cplusplus
extern "C"
{
#endif

status_t _getJsonStatus(json_object *obj)
{

	status_t status;
	memset(&status, 0x00, sizeof(status_t));

	if(obj)
	{
		asprintf(&status.created_at, "%s", json_object_to_json_string(json_object_object_get(obj,"created_at")));
		asprintf(&status.id, "%s", json_object_to_json_string(json_object_object_get(obj,"id")));
		asprintf(&status.text, "%s", json_object_to_json_string(json_object_object_get(obj,"text")));
		asprintf(&status.source, "%s", json_object_to_json_string(json_object_object_get(obj,"source")));
		asprintf(&status.truncated, "%s", json_object_to_json_string(json_object_object_get(obj,"truncated")));
		asprintf(&status.favorited, "%s", json_object_to_json_string(json_object_object_get(obj,"favorited")));
		asprintf(&status.in_reply_to_status_id, "%s", json_object_to_json_string(json_object_object_get(obj,"in_reply_to_status_id")));
		asprintf(&status.in_reply_to_user_id, "%s", json_object_to_json_string(json_object_object_get(obj,"in_reply_to_user_id")));
		asprintf(&status.in_reply_to_screen_name, "%s", json_object_to_json_string(json_object_object_get(obj,"in_reply_to_screen_name")));
		asprintf(&status.retweet_count, "%s", json_object_to_json_string(json_object_object_get(obj,"retweet_count")));
		asprintf(&status.retweeted, "%s", json_object_to_json_string(json_object_object_get(obj,"retweeted")));
		asprintf(&status.geo, "%s", json_object_to_json_string(json_object_object_get(obj,"geo")));
		asprintf(&status.coordinates, "%s", json_object_to_json_string(json_object_object_get(obj,"coordinates")));
		asprintf(&status.place, "%s", json_object_to_json_string(json_object_object_get(obj,"place")));
		asprintf(&status.contributors, "%s", json_object_to_json_string(json_object_object_get(obj,"contributors")));

		json_object *user=json_object_object_get(obj,"user");

		asprintf(&status.user.id, "%s", json_object_to_json_string(json_object_object_get(user,"id")));
		asprintf(&status.user.name, "%s", json_object_to_json_string(json_object_object_get(user,"name")));
		asprintf(&status.user.screen_name, "%s", json_object_to_json_string(json_object_object_get(user,"screen_name")));
		asprintf(&status.user.location, "%s", json_object_to_json_string(json_object_object_get(user,"location")));
		asprintf(&status.user.description, "%s", json_object_to_json_string(json_object_object_get(user,"description")));
		asprintf(&status.user.profile_image_url, "%s", json_object_to_json_string(json_object_object_get(user,"profile_image_url")));
		asprintf(&status.user.profile_image, "%s", json_object_to_json_string(json_object_object_get(user,"profile_image")));
		asprintf(&status.user.url, "%s", json_object_to_json_string(json_object_object_get(user,"url")));
		asprintf(&status.user.protected, "%s", json_object_to_json_string(json_object_object_get(user,"protected")));
		asprintf(&status.user.profile_background_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_background_color")));
		asprintf(&status.user.profile_text_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_text_color")));
		asprintf(&status.user.profile_link_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_link_color")));
		asprintf(&status.user.profile_sidebar_fill_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_sidebar_fill_color")));
		asprintf(&status.user.profile_sidebar_border_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_sidebar_border_color")));
		asprintf(&status.user.created_at, "%s", json_object_to_json_string(json_object_object_get(user,"created_at")));
		asprintf(&status.user.utc_offset, "%s", json_object_to_json_string(json_object_object_get(user,"utc_offset")));
		asprintf(&status.user.time_zone, "%s", json_object_to_json_string(json_object_object_get(user,"time_zone")));
		asprintf(&status.user.profile_background_image_url, "%s", json_object_to_json_string(json_object_object_get(user,"profile_background_image_url")));
		asprintf(&status.user.profile_background_tile, "%s", json_object_to_json_string(json_object_object_get(user,"profile_background_tile")));
		asprintf(&status.user.profile_use_background_image, "%s", json_object_to_json_string(json_object_object_get(user,"profile_use_background_image")));
		asprintf(&status.user.notifications, "%s", json_object_to_json_string(json_object_object_get(user,"notifications")));
		asprintf(&status.user.geo_enabled, "%s", json_object_to_json_string(json_object_object_get(user,"geo_enabled")));
		asprintf(&status.user.verified, "%s", json_object_to_json_string(json_object_object_get(user,"verified")));
		asprintf(&status.user.following, "%s", json_object_to_json_string(json_object_object_get(user,"following")));
		asprintf(&status.user.lang, "%s", json_object_to_json_string(json_object_object_get(user,"lang")));
		asprintf(&status.user.contributors_enabled, "%s", json_object_to_json_string(json_object_object_get(user,"contributors_enabled")));
		asprintf(&status.user.follow_request_sent, "%s", json_object_to_json_string(json_object_object_get(user,"follow_request_sent")));
		asprintf(&status.user.show_all_inline_media, "%s", json_object_to_json_string(json_object_object_get(user,"show_all_inline_media")));
		asprintf(&status.user.default_profile, "%s", json_object_to_json_string(json_object_object_get(user,"default_profile")));
		asprintf(&status.user.default_profile_image, "%s", json_object_to_json_string(json_object_object_get(user,"default_profile_image")));
		asprintf(&status.user.is_translator, "%s", json_object_to_json_string(json_object_object_get(user,"is_translator")));
		asprintf(&status.user.followers_count, "%s", json_object_to_json_string(json_object_object_get(user,"followers_count")));
		asprintf(&status.user.friends_count, "%s", json_object_to_json_string(json_object_object_get(user,"friends_count")));
		asprintf(&status.user.favourites_count, "%s", json_object_to_json_string(json_object_object_get(user,"favourites_count")));
		asprintf(&status.user.statuses_count, "%s", json_object_to_json_string(json_object_object_get(user,"statuses_count")));
		asprintf(&status.user.listed_count, "%s", json_object_to_json_string(json_object_object_get(user,"listed_count")));

		json_object_put(user);
	}

	return status;
}

/*
 *
 * Don't Work!!
 *
 */
status_t getJsonStatus(const string_t rawStatus)
{

	status_t status;
	memset(&status, 0x00, sizeof(status_t));

	json_object *obj = json_tokener_parse(rawStatus);
	status=_getJsonStatus(obj);

	json_object_put(obj);


	return status;

}


status_t getStatus(const string_t rawStatus){

return getJsonStatus(rawStatus);
}

/*
 * Send a tweet with User-Keys (token) and TwitCrusader-Keys (token)
 *
 */
string_t
updateStatus(const twitterURLS_t * twURLS, const user_t * user, const string_t msg)
{

	string_t output = NULL;

	if (twURLS && user && msg)
	{
		string_t url = NULL;

		/*
		 * Send Tweet with oAuth functions
		 */
		url = componeAPI_URL(twURLS, Http, STATUSUPDATE_URL);

		string_t tweet = oauth_url_escape(msg);
		if (tweet)
		{
			string_t twitterStatusURL = NULL;
			asprintf(&twitterStatusURL, "%s%s%s%s%s", url, URL_SEP_QUES, "status", "=", tweet);

			if (twitterStatusURL)
			{
				if (user->id && user->screenName && user->consumerKey
						&& user->consumerSecretKey && user->token
						&& user->secretToken)
				{

					string_t postarg = NULL;
					string_t sendTweet = oauth_sign_url2(twitterStatusURL,
							&postarg, OA_HMAC, NULL, user->consumerKey,
							user->consumerSecretKey, user->token, user->secretToken);

					if (sendTweet)
						output = oauth_http_post(sendTweet, postarg);

					if (sendTweet)
						free(sendTweet);
					if (postarg)
						free(postarg);

					sendTweet = NULL;
					postarg = NULL;

				}
			}

			if (twitterStatusURL)
				free(twitterStatusURL);
			twitterStatusURL = NULL;

		}
		if (tweet)
			free(tweet);
		if (url)
			free(url);

		tweet = NULL;
		url = NULL;

	}

	return output;
}

void
uninitTwitterUser(twitterUser_t twUser)
{

	if (twUser.id)
		free(twUser.id);
	if (twUser.name)
		free(twUser.name);
	if (twUser.screen_name)
		free(twUser.screen_name);
	if (twUser.location)
		free(twUser.location);
	if (twUser.description)
		free(twUser.description);
	if (twUser.profile_image_url)
		free(twUser.profile_image_url);
	if (twUser.profile_image)
		free(twUser.profile_image);
	if (twUser.url)
		free(twUser.url);
	if (twUser.protected)
		free(twUser.protected);
	if (twUser.profile_background_color)
		free(twUser.profile_background_color);
	if (twUser.profile_text_color)
		free(twUser.profile_text_color);
	if (twUser.profile_link_color)
		free(twUser.profile_link_color);
	if (twUser.profile_sidebar_fill_color)
		free(twUser.profile_sidebar_fill_color);
	if (twUser.profile_sidebar_border_color)
		free(twUser.profile_sidebar_border_color);
	if (twUser.created_at)
		free(twUser.created_at);
	if (twUser.utc_offset)
		free(twUser.utc_offset);
	if (twUser.time_zone)
		free(twUser.time_zone);
	if (twUser.profile_background_image_url)
		free(twUser.profile_background_image_url);
	if (twUser.profile_background_tile)
		free(twUser.profile_background_tile);
	if (twUser.profile_use_background_image)
		free(twUser.profile_use_background_image);
	if (twUser.notifications)
		free(twUser.notifications);
	if (twUser.geo_enabled)
		free(twUser.geo_enabled);
	if (twUser.verified)
		free(twUser.verified);
	if (twUser.following)
		free(twUser.following);
	if (twUser.lang)
		free(twUser.lang);
	if (twUser.contributors_enabled)
		free(twUser.contributors_enabled);
	if (twUser.follow_request_sent)
		free(twUser.follow_request_sent);
	if (twUser.show_all_inline_media)
		free(twUser.show_all_inline_media);
	if (twUser.default_profile)
		free(twUser.default_profile);
	if (twUser.default_profile_image)
		free(twUser.default_profile_image);
	if (twUser.is_translator)
		free(twUser.is_translator);
	if (twUser.followers_count)
		free(twUser.followers_count);
	if (twUser.friends_count)
		free(twUser.friends_count);
	if (twUser.favourites_count)
		free(twUser.favourites_count);
	if (twUser.statuses_count)
		free(twUser.statuses_count);
	if (twUser.listed_count)
		free(twUser.listed_count);

	twUser.id = NULL;
	twUser.name = NULL;
	twUser.screen_name = NULL;
	twUser.location = NULL;
	twUser.description = NULL;
	twUser.profile_image_url = NULL;
	twUser.profile_image = NULL;
	twUser.url = NULL;
	twUser.protected = NULL;
	twUser.profile_background_color = NULL;
	twUser.profile_text_color = NULL;
	twUser.profile_link_color = NULL;
	twUser.profile_sidebar_fill_color = NULL;
	twUser.profile_sidebar_border_color = NULL;
	twUser.created_at = NULL;
	twUser.utc_offset = NULL;
	twUser.time_zone = NULL;
	twUser.profile_background_image_url = NULL;
	twUser.profile_background_tile = NULL;
	twUser.profile_use_background_image = NULL;
	twUser.notifications = NULL;
	twUser.geo_enabled = NULL;
	twUser.verified = NULL;
	twUser.following = NULL;
	twUser.lang = NULL;
	twUser.contributors_enabled = NULL;
	twUser.follow_request_sent = NULL;
	twUser.show_all_inline_media = NULL;
	twUser.default_profile = NULL;
	twUser.default_profile_image = NULL;
	twUser.is_translator = NULL;
	twUser.followers_count = NULL;
	twUser.friends_count = NULL;
	twUser.favourites_count = NULL;
	twUser.statuses_count = NULL;
	twUser.listed_count = NULL;

}

void
uninitStatus(status_t status)
{

	uninitTwitterUser(status.user);
	if (status.created_at)
		free(status.created_at);
	if (status.id)
		free(status.id);
	if (status.text)
		free(status.text);
	if (status.source)
		free(status.source);
	if (status.truncated)
		free(status.truncated);
	if (status.favorited)
		free(status.favorited);
	if (status.in_reply_to_status_id)
		free(status.in_reply_to_status_id);
	if (status.in_reply_to_user_id)
		free(status.in_reply_to_user_id);
	if (status.in_reply_to_screen_name)
		free(status.in_reply_to_screen_name);
	if (status.retweet_count)
		free(status.retweet_count);
	if (status.retweeted)
		free(status.retweeted);
	if (status.geo)
		free(status.geo);
	if (status.coordinates)
		free(status.coordinates);
	if (status.place)
		free(status.place);
	if (status.contributors)
		free(status.contributors);

	status.created_at = NULL;
	status.id = NULL;
	status.text = NULL;
	status.source = NULL;
	status.truncated = NULL;
	status.favorited = NULL;
	status.in_reply_to_status_id = NULL;
	status.in_reply_to_user_id = NULL;
	status.in_reply_to_screen_name = NULL;
	status.retweet_count = NULL;
	status.retweeted = NULL;
	status.geo = NULL;
	status.coordinates = NULL;
	status.place = NULL;
	status.contributors = NULL;
}


#ifdef __cplusplus
}
#endif

