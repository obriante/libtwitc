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

#ifndef STATUS_H_
#define STATUS_H_

typedef struct
{
  string_t id;
  string_t name;
  string_t screen_name;
  string_t location;
  string_t description;
  string_t profile_image_url;
  string_t profile_image;
  string_t url;
  string_t protected;
  string_t profile_background_color;
  string_t profile_text_color;
  string_t profile_link_color;
  string_t profile_sidebar_fill_color;
  string_t profile_sidebar_border_color;
  string_t created_at;
  string_t utc_offset;
  string_t time_zone;
  string_t profile_background_image_url;
  string_t profile_background_tile;
  string_t profile_use_background_image;
  string_t notifications;
  string_t geo_enabled;
  string_t verified;
  string_t following;
  string_t lang;
  string_t contributors_enabled;
  string_t follow_request_sent;
  string_t show_all_inline_media;
  string_t default_profile;
  string_t default_profile_image;
  string_t is_translator;
  string_t followers_count;
  string_t friends_count;
  string_t favourites_count;
  string_t statuses_count;
  string_t listed_count;
} twitterUser_t;

typedef struct
{
  twitterUser_t user;
  string_t created_at;
  string_t id;
  string_t text;
  string_t source;
  string_t truncated;
  string_t favorited;
  string_t in_reply_to_status_id;
  string_t in_reply_to_user_id;
  string_t in_reply_to_screen_name;
  string_t retweet_count;
  string_t retweeted;
  string_t geo;
  string_t coordinates;
  string_t place;
  string_t contributors;
} status_t;


extern status_t
getStatus(const string_t);

extern string_t
updateStatus(const twitterURLS_t * twURLS, const user_t * user, const string_t msg, const ApiFormatType_t apiFormatType);

extern void
uninitTwitterUser(twitterUser_t);

extern void
uninitStatus(status_t);

#endif /* STATUS_H_ */
