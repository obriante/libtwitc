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

timeline_t readXMLTimeLine(const string_t rawTimeline)
{

	timeline_t timeline;
	memset(&timeline, 0x00, sizeof(timeline));

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

	return timeline;
}


timeline_t readJsonTimeLine(const string_t rawTimeline)
{

	timeline_t timeline;
	memset(&timeline, 0x00, sizeof(timeline));

	return timeline;
}

timeline_t readTimeLine(const string_t rawTimeline)
{

	timeline_t timeline;
	memset(&timeline, 0x00, sizeof(timeline));

	if(rawTimeline)
	{
		if(xmlReadMemory(rawTimeline, strlen(rawTimeline), "", NULL, XML_PARSE_COMPACT))
		{
			debug("%s", "timeline is a XML File");

			timeline=readXMLTimeLine(rawTimeline);
		}
		else
		{
			debug("%s", "timeline is a JSON File");

			timeline=readJsonTimeLine(rawTimeline);
		}

	}

	return timeline;
}

#ifdef __cplusplus
}
#endif
