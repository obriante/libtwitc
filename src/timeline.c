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

#include <twitc/debug.h>
#include <twitc/timeline.h>
#include <twitc/user.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <json.h>


#ifdef __cplusplus
extern "C"{
#endif

timelineElement_t getStatus (const xmlDocPtr doc, xmlNodePtr cur)
{

	timelineElement_t timeL;
	memset(&timeL, 0x00, sizeof(timelineElement_t));

	if(doc && cur)
	{
		cur = cur->xmlChildrenNode->next;

		while(cur)
		{
			//*created_at
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"created_at")))
				asprintf(&timeL.created_at, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));



			// *id,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"id")))
				asprintf(&timeL.id, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));



			// *text,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"text")))
				asprintf(&timeL.text, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));


			// *source,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"source")))
				asprintf(&timeL.source, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));


			// *truncated,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"truncated")))
				asprintf(&timeL.truncated, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			// *favorited,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"favorited")))
				asprintf(&timeL.favorited, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			// *in_reply_to_status_id,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"in_reply_to_status_id")))
				asprintf(&timeL.in_reply_to_status_id, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			// *in_reply_to_user_id,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"in_reply_to_user_id")))
				asprintf(&timeL.in_reply_to_user_id, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			// *in_reply_to_screen_name,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"in_reply_to_screen_name")))
				asprintf(&timeL.in_reply_to_screen_name, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			// *retweet_count,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"retweet_count")))
				asprintf(&timeL.retweet_count, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			// *retweeted,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"retweeted")))
				asprintf(&timeL.retweeted, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			//struct user_timeline pub_user;
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"user"))) {

				xmlNodePtr cur2 = cur->xmlChildrenNode->next;

				while(cur2)
				{
					// char *id,
					if ((!xmlStrcmp(cur2->name, (const xmlChar *)"id")))
						asprintf(&timeL.user.id, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *name,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"name")))
						asprintf(&timeL.user.name, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *screen_name,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"screen_name")))
						asprintf(&timeL.user.screen_name, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *location,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"location")))
						asprintf(&timeL.user.location, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *description,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"description")))
						asprintf(&timeL.user.description, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *profile_image_url,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"profile_image_url")))
						asprintf(&timeL.user.profile_image_url, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *url,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"url")))
						asprintf(&timeL.user.url, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *protected,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"protected")))
						asprintf(&timeL.user.protected, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *profile_background_color,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"profile_background_color")))
						asprintf(&timeL.user.profile_background_color, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));


					// *profile_text_color,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"profile_text_color")))
						asprintf(&timeL.user.profile_text_color, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *profile_link_color,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"profile_link_color")))
						asprintf(&timeL.user.profile_link_color, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *profile_sidebar_fill_color,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"profile_sidebar_fill_color")))
						asprintf(&timeL.user.profile_sidebar_fill_color, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *profile_sidebar_border_color,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"profile_sidebar_border_color")))
						asprintf(&timeL.user.profile_sidebar_border_color, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *created_at,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"created_at")))
						asprintf(&timeL.user.created_at, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *utc_offset,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"utc_offset")))
						asprintf(&timeL.user.utc_offset, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *time_zone,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"time_zone")))
						asprintf(&timeL.user.time_zone, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *profile_background_image_url,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"profile_background_image_url")))
						asprintf(&timeL.user.profile_background_image_url, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *profile_background_tile,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"profile_background_tile")))
						asprintf(&timeL.user.profile_background_tile, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *profile_use_background_image,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"profile_use_background_image")))
						asprintf(&timeL.user.profile_use_background_image, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *notifications,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"notifications")))
						asprintf(&timeL.user.notifications, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *geo_enabled,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"geo_enabled")))
						asprintf(&timeL.user.geo_enabled, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *verified,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"verified")))
						asprintf(&timeL.user.verified, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *following,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"following")))
						asprintf(&timeL.user.following, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *lang,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"lang")))
						asprintf(&timeL.user.lang, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *contributors_enabled,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"contributors_enabled")))
						asprintf(&timeL.user.contributors_enabled, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *follow_request_sent,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"follow_request_sent")))
						asprintf(&timeL.user.follow_request_sent, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *show_all_inline_media,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"show_all_inline_media")))
						asprintf(&timeL.user.show_all_inline_media, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *default_profile,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"default_profile")))
						asprintf(&timeL.user.default_profile, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *default_profile_image,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"default_profile_image")))
						asprintf(&timeL.user.default_profile_image, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *is_translator,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"is_translator")))
						asprintf(&timeL.user.is_translator, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *followers_count,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"followers_count")))
						asprintf(&timeL.user.followers_count, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *friends_count,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"friends_count")))
						asprintf(&timeL.user.friends_count, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// *favourites_count,
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"favourites_count")))
						asprintf(&timeL.user.favourites_count, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// statuses_count, ;
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"statuses_count")))
						asprintf(&timeL.user.statuses_count, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					// listed_count
					else if ((!xmlStrcmp(cur2->name, (const xmlChar *)"listed_count")))
						asprintf(&timeL.user.listed_count, "%s", xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

					cur2 = cur2->next;
					cur2 = cur2->next;
				}
			}


			// *geo,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"geo")))
				asprintf(&timeL.geo, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			// *coordinates,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"coordinates")))
				asprintf(&timeL.coordinates, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			// *place,
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"place")))
				asprintf(&timeL.place, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			// *contributors;
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"contributors")))
				asprintf(&timeL.contributors, "%s", xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

			cur = cur->next;
			cur = cur->next;
		}

	}

	return timeL;
}


timeline_t readXmlTimeLine(const string_t rawTimeline)
{

	timeline_t timeline;
	memset(&timeline, 0x00, sizeof(timeline));

	if(rawTimeline)
	{

		xmlDocPtr doc = xmlReadMemory(rawTimeline, strlen(rawTimeline), "", NULL, XML_PARSE_COMPACT);

		if (doc)
		{
			xmlNodePtr cur = xmlDocGetRootElement(doc);

			while (cur)
			{

				if (!xmlStrcmp(cur->name, (const xmlChar *) "statuses"))
				{

					debug("cur->name: %s", cur->name);

					cur = cur->xmlChildrenNode;

					int i=0;
					while (cur)
					{
						if ((!xmlStrcmp(cur->name, (const xmlChar *)"status")))
						{
							debug("cur->name: %s", cur->name);

							timeline.timeline[i]=getStatus(doc, cur);

							debug(" %i) [%s] @%s: %s", i, timeline.timeline[i].created_at, timeline.timeline[i].user.screen_name, timeline.timeline[i].text);
							i++;
						}

						cur = cur->next;

					}
				}
			}

			xmlFreeDoc(doc);

		}
	}

	return timeline;
}



timeline_t readJsonTimeLine(const string_t rawTimeline)
{

	int i=0;
	timeline_t timeline;
	memset(&timeline, 0x00, sizeof(timeline));

	json_object *obj = json_tokener_parse(rawTimeline);

	for(i=0; i<json_object_array_length(obj); i++)
	{
		asprintf(&timeline.timeline[i].created_at, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"created_at")));
		asprintf(&timeline.timeline[i].id, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"id")));
		asprintf(&timeline.timeline[i].text, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"text")));
		asprintf(&timeline.timeline[i].source, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"source")));
		asprintf(&timeline.timeline[i].truncated, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"truncated")));
		asprintf(&timeline.timeline[i].favorited, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"favorited")));
		asprintf(&timeline.timeline[i].in_reply_to_status_id, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"in_reply_to_status_id")));
		asprintf(&timeline.timeline[i].in_reply_to_user_id, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"in_reply_to_user_id")));
		asprintf(&timeline.timeline[i].in_reply_to_screen_name, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"in_reply_to_screen_name")));
		asprintf(&timeline.timeline[i].retweet_count, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"retweet_count")));
		asprintf(&timeline.timeline[i].retweeted, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"retweeted")));
		asprintf(&timeline.timeline[i].geo, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"geo")));
		asprintf(&timeline.timeline[i].coordinates, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"coordinates")));
		asprintf(&timeline.timeline[i].place, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"place")));
		asprintf(&timeline.timeline[i].contributors, "%s", json_object_to_json_string(json_object_object_get(json_object_array_get_idx(obj,i),"contributors")));

		json_object *user=json_object_object_get(json_object_array_get_idx(obj,i),"user");

		asprintf(&timeline.timeline[i].user.id, "%s", json_object_to_json_string(json_object_object_get(user,"id")));
		asprintf(&timeline.timeline[i].user.name, "%s", json_object_to_json_string(json_object_object_get(user,"name")));
		asprintf(&timeline.timeline[i].user.screen_name, "%s", json_object_to_json_string(json_object_object_get(user,"screen_name")));
		asprintf(&timeline.timeline[i].user.location, "%s", json_object_to_json_string(json_object_object_get(user,"location")));
		asprintf(&timeline.timeline[i].user.description, "%s", json_object_to_json_string(json_object_object_get(user,"description")));
		asprintf(&timeline.timeline[i].user.profile_image_url, "%s", json_object_to_json_string(json_object_object_get(user,"profile_image_url")));
		asprintf(&timeline.timeline[i].user.profile_image, "%s", json_object_to_json_string(json_object_object_get(user,"profile_image")));
		asprintf(&timeline.timeline[i].user.url, "%s", json_object_to_json_string(json_object_object_get(user,"url")));
		asprintf(&timeline.timeline[i].user.protected, "%s", json_object_to_json_string(json_object_object_get(user,"protected")));
		asprintf(&timeline.timeline[i].user.profile_background_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_background_color")));
		asprintf(&timeline.timeline[i].user.profile_text_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_text_color")));
		asprintf(&timeline.timeline[i].user.profile_link_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_link_color")));
		asprintf(&timeline.timeline[i].user.profile_sidebar_fill_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_sidebar_fill_color")));
		asprintf(&timeline.timeline[i].user.profile_sidebar_border_color, "%s", json_object_to_json_string(json_object_object_get(user,"profile_sidebar_border_color")));
		asprintf(&timeline.timeline[i].user.created_at, "%s", json_object_to_json_string(json_object_object_get(user,"created_at")));
		asprintf(&timeline.timeline[i].user.utc_offset, "%s", json_object_to_json_string(json_object_object_get(user,"utc_offset")));
		asprintf(&timeline.timeline[i].user.time_zone, "%s", json_object_to_json_string(json_object_object_get(user,"time_zone")));
		asprintf(&timeline.timeline[i].user.profile_background_image_url, "%s", json_object_to_json_string(json_object_object_get(user,"profile_background_image_url")));
		asprintf(&timeline.timeline[i].user.profile_background_tile, "%s", json_object_to_json_string(json_object_object_get(user,"profile_background_tile")));
		asprintf(&timeline.timeline[i].user.profile_use_background_image, "%s", json_object_to_json_string(json_object_object_get(user,"profile_use_background_image")));
		asprintf(&timeline.timeline[i].user.notifications, "%s", json_object_to_json_string(json_object_object_get(user,"notifications")));
		asprintf(&timeline.timeline[i].user.geo_enabled, "%s", json_object_to_json_string(json_object_object_get(user,"geo_enabled")));
		asprintf(&timeline.timeline[i].user.verified, "%s", json_object_to_json_string(json_object_object_get(user,"verified")));
		asprintf(&timeline.timeline[i].user.following, "%s", json_object_to_json_string(json_object_object_get(user,"following")));
		asprintf(&timeline.timeline[i].user.lang, "%s", json_object_to_json_string(json_object_object_get(user,"lang")));
		asprintf(&timeline.timeline[i].user.contributors_enabled, "%s", json_object_to_json_string(json_object_object_get(user,"contributors_enabled")));
		asprintf(&timeline.timeline[i].user.follow_request_sent, "%s", json_object_to_json_string(json_object_object_get(user,"follow_request_sent")));
		asprintf(&timeline.timeline[i].user.show_all_inline_media, "%s", json_object_to_json_string(json_object_object_get(user,"show_all_inline_media")));
		asprintf(&timeline.timeline[i].user.default_profile, "%s", json_object_to_json_string(json_object_object_get(user,"default_profile")));
		asprintf(&timeline.timeline[i].user.default_profile_image, "%s", json_object_to_json_string(json_object_object_get(user,"default_profile_image")));
		asprintf(&timeline.timeline[i].user.is_translator, "%s", json_object_to_json_string(json_object_object_get(user,"is_translator")));
		asprintf(&timeline.timeline[i].user.followers_count, "%s", json_object_to_json_string(json_object_object_get(user,"followers_count")));
		asprintf(&timeline.timeline[i].user.friends_count, "%s", json_object_to_json_string(json_object_object_get(user,"friends_count")));
		asprintf(&timeline.timeline[i].user.favourites_count, "%s", json_object_to_json_string(json_object_object_get(user,"favourites_count")));
		asprintf(&timeline.timeline[i].user.statuses_count, "%s", json_object_to_json_string(json_object_object_get(user,"statuses_count")));
		asprintf(&timeline.timeline[i].user.listed_count, "%s", json_object_to_json_string(json_object_object_get(user,"listed_count")));

		json_object_put(user);
	}

	json_object_put(obj);

	return timeline;
}

#ifdef __cplusplus
}
#endif
