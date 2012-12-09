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

#ifndef DM_H_
#define DM_H_

#define         MAX_NUM_DM  200



#include <twitc/stdredef.h>

typedef struct{
  string_t id;
  string_t name;
  string_t screen_name;
  string_t location;
  string_t description;
  string_t profile_image_url;
  string_t profile_image_url_https;
  string_t url;
  string_t protected;
  string_t followers_count;
  string_t profile_background_color;
  string_t profile_text_color;
  string_t profile_link_color;
  string_t profile_sidebar_fill_color;
  string_t profile_sidebar_border_color;
  string_t friends_count;
  string_t created_at;
  string_t favourites_count;
  string_t utc_offset;
  string_t time_zone;
  string_t profile_background_image_url;
  string_t profile_background_image_url_https;
  string_t profile_background_tile;
  string_t profile_use_background_image;
  string_t notifications;
  string_t geo_enabled;
  string_t verified;
  string_t following;
  string_t statuses_count;
  string_t lang;
  string_t contributors_enabled;
  string_t follow_request_sent;
  string_t listed_count;
  string_t show_all_inline_media;
  string_t default_profile;
  string_t default_profile_image;
  string_t is_translator;
}dm_user_t;

typedef struct{
  string_t id;
  string_t sender_id;
  string_t text;
  string_t recipient_id;
  string_t created_at;
  string_t sender_screen_name;
  string_t recipient_screen_name;
  dm_user_t sender;
  dm_user_t recipient;
}direct_message_t;


typedef struct{

  direct_message_t directMessage[MAX_NUM_DM];

}direct_messages_t;

extern string_t
getRawDM(const twitterURLS_t *, const user_t *);

extern string_t
getRawSentDM(const twitterURLS_t *, const user_t *);

extern string_t
sendDM(const twitterURLS_t *, const user_t *, const string_t, const string_t);

extern direct_messages_t
getDMs(const string_t);


extern void
uninitDMUser(dm_user_t);


extern void
uninitDM(direct_message_t);

extern void uninitDirectMessages(direct_messages_t *);



#endif /* DM_H_ */
