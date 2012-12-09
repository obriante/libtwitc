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

#include <logc/logc.h>

#include <twitc/http.h>
#include <twitc/timeline.h>
#include <twitc/user.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <oauth.h>
#include <libxml/xmlreader.h>
#include <json.h>

#ifdef __cplusplus
extern "C"{
#endif


extern status_t _getXmlStatus(const xmlDocPtr, xmlNodePtr);


extern status_t _getJsonStatus(json_object *obj);



string_t
getRawTimeline(const twitterURLS_t * twURLS, timelineType_t timelineType, const user_t * user)
{

	string_t timeline = NULL;
	string_t url = NULL;

	if (timelineType == home_timeline)
	{
		url = componeAPI_URL(twURLS, Http, HOME_TIMELINE_URL);
	}
	else if (timelineType == featured)
	{
		url = componeAPI_URL(twURLS, Http, FEATURED_USERS_URL);
	}
	else if (timelineType == friends_timeline)
	{
		url = componeAPI_URL(twURLS, Http, FRIENDS_TIMELINE_URL);
	}
	else if (timelineType == mentions)
	{
		url = componeAPI_URL(twURLS, Http, MENTIONS_URL);
	}
	else if (timelineType == user_timeline)
	{
		url = componeAPI_URL(twURLS, Http, USERTIMELINE_URL);
	}
	else if (timelineType == public_timeline)
	{
		url = componeAPI_URL(twURLS, Http, PUBLIC_TIMELINE_URL);
	}
	else
	{
		url = componeAPI_URL(twURLS, Http, PUBLIC_TIMELINE_URL);
	}

	if (url)
	{
		string_t req_url = NULL;
		asprintf(&req_url, "%s%s", url, URL_SEP_QUES);

		if (user)
			req_url = oauth_sign_url2(req_url, NULL, OA_HMAC, NULL,
					user->consumerKey, user->consumerSecretKey, user->token,
					user->secretToken);
		else
			req_url = oauth_sign_url2(req_url, NULL, OA_HMAC, NULL, NULL, NULL,
					NULL, NULL );

		if (req_url)
		{
			debug ("req_url :\t%s", req_url);

			timeline = oauth_http_get(req_url, NULL );

		}

		if (req_url)
			free(req_url);
		req_url = NULL;
	}

	if (url)
		free(url);
	url = NULL;

	if (!timeline)
		log(WARNING,"Returned value: (NULL)");

	return timeline;
}


timeline_t readXmlTimeLine(const string_t rawTimeline)
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

						timeline.statuses[i]=_getXmlStatus(doc, cur);

						debug(" %i) [%s] @%s: %s", i, timeline.statuses[i].created_at, timeline.statuses[i].user.screen_name, timeline.statuses[i].text);
						i++;
					}

					cur = cur->next;

				}
			}else
				cur = cur->next;
		}
	}

	if(doc)
		xmlFreeDoc(doc);


	return timeline;
}

timeline_t readJsonTimeLine(const string_t rawTimeline)
{

	int i=0;
	timeline_t timeline;
	memset(&timeline, 0x00, sizeof(timeline));

	json_object *obj = json_tokener_parse(rawTimeline);

	if(obj)
	{
		for(i=0; i<json_object_array_length(obj); i++)
		{

			if(json_object_object_get(obj,"errors"))
								return timeline;

			timeline.statuses[i]=_getJsonStatus(json_object_array_get_idx(obj,i));
		}
	}

	return timeline;
}


timeline_t readTimeLine(const string_t rawTimeline)
{

	json_object *obj = json_tokener_parse(rawTimeline);

	if(obj)
		return readJsonTimeLine(rawTimeline);


	return 	readXmlTimeLine(rawTimeline);
}

void uninitTimeline(timeline_t *timeline)
{
	int i = 0;

	for (i = 0; i < MAX_NUM_TWEETS; i++)
		if(timeline->statuses[i].text)
			uninitStatus(timeline->statuses[i]);

	memset(timeline, 0x00, sizeof(timeline_t));

}


#ifdef __cplusplus
}
#endif
