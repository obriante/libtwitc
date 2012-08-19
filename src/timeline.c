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
#include <twitc/http.h>
#include <twitc/timeline.h>
#include <twitc/user.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <oauth.h>

#ifdef __cplusplus
extern "C"
  {
#endif

status_t
_getXmlStatus(const xmlDocPtr doc, xmlNodePtr cur)
{

  status_t status;
  memset(&status, 0x00, sizeof(status_t));

  if (cur)
    {
      cur = cur->xmlChildrenNode->next;

      while (cur)
        {
          // *created_at
          if ((!xmlStrcmp(cur->name, (const xmlChar *) "created_at")))
            asprintf(&status.created_at, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *id,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "id")))
            asprintf(&status.id, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *text,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "text")))
            asprintf(&status.text, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *source,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "source")))
            asprintf(&status.source, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *truncated,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "truncated")))
            asprintf(&status.truncated, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *favorited,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "favorited")))
            asprintf(&status.favorited, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *in_reply_to_status_id,
          else if ((!xmlStrcmp(cur->name,
              (const xmlChar *) "in_reply_to_status_id")))
            asprintf(&status.in_reply_to_status_id, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *in_reply_to_user_id,
          else if ((!xmlStrcmp(cur->name,
              (const xmlChar *) "in_reply_to_user_id")))
            asprintf(&status.in_reply_to_user_id, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *in_reply_to_screen_name,
          else if ((!xmlStrcmp(cur->name,
              (const xmlChar *) "in_reply_to_screen_name")))
            asprintf(&status.in_reply_to_screen_name, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *retweet_count,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "retweet_count")))
            asprintf(&status.retweet_count, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *retweeted,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "retweeted")))
            asprintf(&status.retweeted, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // struct user_timeline pub_user;
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "user")))
            {

              xmlNodePtr cur2 = cur->xmlChildrenNode->next;

              while (cur2)
                {
                  // char *id,
                  if ((!xmlStrcmp(cur2->name, (const xmlChar *) "id")))
                    asprintf(&status.user.id, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *name,
                  else if ((!xmlStrcmp(cur2->name, (const xmlChar *) "name")))
                    asprintf(&status.user.name, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *screen_name,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "screen_name")))
                    asprintf(&status.user.screen_name, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *location,
                  else if ((!xmlStrcmp(cur2->name, (const xmlChar *) "location")))
                    asprintf(&status.user.location, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *description,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "description")))
                    asprintf(&status.user.description, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *profile_image_url,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "profile_image_url")))
                    asprintf(&status.user.profile_image_url, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *url,
                  else if ((!xmlStrcmp(cur2->name, (const xmlChar *) "url")))
                    asprintf(&status.user.url, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *protected,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "protected")))
                    asprintf(&status.user.protected, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *profile_background_color,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "profile_background_color")))
                    asprintf(&status.user.profile_background_color, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *profile_text_color,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "profile_text_color")))
                    asprintf(&status.user.profile_text_color, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *profile_link_color,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "profile_link_color")))
                    asprintf(&status.user.profile_link_color, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *profile_sidebar_fill_color,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "profile_sidebar_fill_color")))
                    asprintf(&status.user.profile_sidebar_fill_color, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *profile_sidebar_border_color,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "profile_sidebar_border_color")))
                    asprintf(&status.user.profile_sidebar_border_color, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *created_at,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "created_at")))
                    asprintf(&status.user.created_at, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *utc_offset,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "utc_offset")))
                    asprintf(&status.user.utc_offset, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *time_zone,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "time_zone")))
                    asprintf(&status.user.time_zone, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *profile_background_image_url,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "profile_background_image_url")))
                    asprintf(&status.user.profile_background_image_url, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *profile_background_tile,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "profile_background_tile")))
                    asprintf(&status.user.profile_background_tile, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *profile_use_background_image,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "profile_use_background_image")))
                    asprintf(&status.user.profile_use_background_image, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *notifications,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "notifications")))
                    asprintf(&status.user.notifications, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *geo_enabled,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "geo_enabled")))
                    asprintf(&status.user.geo_enabled, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *verified,
                  else if ((!xmlStrcmp(cur2->name, (const xmlChar *) "verified")))
                    asprintf(&status.user.verified, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *following,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "following")))
                    asprintf(&status.user.following, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *lang,
                  else if ((!xmlStrcmp(cur2->name, (const xmlChar *) "lang")))
                    asprintf(&status.user.lang, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *contributors_enabled,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "contributors_enabled")))
                    asprintf(&status.user.contributors_enabled, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *follow_request_sent,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "follow_request_sent")))
                    asprintf(&status.user.follow_request_sent, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *show_all_inline_media,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "show_all_inline_media")))
                    asprintf(&status.user.show_all_inline_media, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *default_profile,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "default_profile")))
                    asprintf(&status.user.default_profile, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *default_profile_image,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "default_profile_image")))
                    asprintf(&status.user.default_profile_image, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *is_translator,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "is_translator")))
                    asprintf(&status.user.is_translator, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *followers_count,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "followers_count")))
                    asprintf(&status.user.followers_count, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *friends_count,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "friends_count")))
                    asprintf(&status.user.friends_count, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // *favourites_count,
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "favourites_count")))
                    asprintf(&status.user.favourites_count, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // statuses_count, ;
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "statuses_count")))
                    asprintf(&status.user.statuses_count, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  // listed_count
                  else if ((!xmlStrcmp(cur2->name,
                      (const xmlChar *) "listed_count")))
                    asprintf(&status.user.listed_count, "%s",
                        xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1));

                  cur2 = cur2->next;
                  cur2 = cur2->next;
                }
            }
          // *geo,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "geo")))
            asprintf(&status.geo, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *coordinates,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "coordinates")))
            asprintf(&status.coordinates, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *place,
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "place")))
            asprintf(&status.place, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          // *contributors;
          else if ((!xmlStrcmp(cur->name, (const xmlChar *) "contributors")))
            asprintf(&status.contributors, "%s",
                xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

          cur = cur->next;
          cur = cur->next;
        }

    }

  return status;
}

status_t
getStatus(const string_t rawStatus)
{

  status_t status;
  memset(&status, 0x00, sizeof(status_t));

  xmlDocPtr doc = xmlReadMemory(rawStatus, strlen(rawStatus), "", NULL,
      XML_PARSE_COMPACT);
  if (doc)
    {
      xmlNodePtr cur = xmlDocGetRootElement(doc);
      status = _getXmlStatus(doc, cur);

    }

  if (doc)
    xmlFreeDoc(doc);

  return status;

}

string_t
getRawTimeline(const twitterURLS_t * twURLS, timelineType_t timelineType,
    const user_t * user)
{

  string_t timeline = NULL;
  string_t url = NULL;

  if (timelineType == home_timeline)
    {
      url = componeAPI_URL(twURLS, Http, HOME_TIMELINE_URL, Xml);
    }
  else if (timelineType == featured)
    {
      url = componeAPI_URL(twURLS, Http, FEATURED_USERS_URL, Xml);
    }
  else if (timelineType == friends_timeline)
    {
      url = componeAPI_URL(twURLS, Http, FRIENDS_TIMELINE_URL, Xml);
    }
  else if (timelineType == mentions)
    {
      url = componeAPI_URL(twURLS, Http, MENTIONS_URL, Xml);
    }
  else if (timelineType == user_timeline)
    {
      url = componeAPI_URL(twURLS, Http, USERTIMELINE_URL, Xml);
    }
  else if (timelineType == public_timeline)
    {
      url = componeAPI_URL(twURLS, Http, PUBLIC_TIMELINE_URL, Xml);
    }
  else
    {
      url = componeAPI_URL(twURLS, Http, PUBLIC_TIMELINE_URL, Xml);
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
    warning("Returned value: (NULL)");

  return timeline;
}

timeline_t
readTimeLine(const string_t rawTimeline)
{

  timeline_t timeline;
  memset(&timeline, 0x00, sizeof(timeline));

  xmlDocPtr doc = xmlReadMemory(rawTimeline, strlen(rawTimeline), "", NULL,
      XML_PARSE_COMPACT);

  if (doc)
    {
      xmlNodePtr cur = xmlDocGetRootElement(doc);

      while (cur)
        {

          if (!xmlStrcmp(cur->name, (const xmlChar *) "statuses"))
            {

              debug ("cur->name: %s", cur->name);

              cur = cur->xmlChildrenNode;

              int i = 0;
              while (cur)
                {
                  if ((!xmlStrcmp(cur->name, (const xmlChar *) "status")))
                    {
                      debug ("cur->name: %s", cur->name);

                      timeline.statuses[i] = _getXmlStatus(doc, cur);

                      debug (" %i) [%s] @%s: %s", i,
                          timeline.statuses[i].created_at,
                          timeline.statuses[i].user.screen_name,
                          timeline.statuses[i].text);
                      i++;
                    }

                  cur = cur->next;

                }
            }
        }
    }

  if (doc)
    xmlFreeDoc(doc);

  return timeline;
}

/* 
 * Send a tweet with User-Keys (token) and TwitCrusader-Keys (token)
 *
 */
string_t
updateStatus(const twitterURLS_t * twURLS, const user_t * user,
    const string_t msg)
{

  string_t output = NULL;

  if (twURLS && user && msg)
    {
      debug ("Message: %s", msg);debug ("screenName: %s", user->screenName);

      string_t url = NULL;

      /* 
       * Send Tweet with oAuth functions 
       */
      url = componeAPI_URL(twURLS, Http, STATUSUPDATE_URL, Xml);

      string_t tweet = oauth_url_escape(msg);
      if (tweet)
        {
          string_t twitterStatusURL = NULL;
          asprintf(&twitterStatusURL, "%s%s%s%s%s", url, URL_SEP_QUES, "status",
              "=", tweet);

          if (twitterStatusURL)
            {
              debug ("twitterStatusURL:\t%s", twitterStatusURL);

              if (user->id && user->screenName && user->consumerKey
                  && user->consumerSecretKey && user->token
                  && user->secretToken)
                {

                  /*DEBUG*/debug ("user->screenName:\t%s", user->screenName);debug ("user->id", user->id);debug ("user->consumerKey", user->consumerKey);debug ("user->consumerSecretKey", user->consumerSecretKey);debug ("user->token", user->token);debug ("user->secretToken", user->secretToken);

                  string_t postarg = NULL;
                  string_t sendTweet = oauth_sign_url2(twitterStatusURL,
                      &postarg, OA_HMAC, NULL, user->consumerKey,
                      user->consumerSecretKey, user->token, user->secretToken);

                  if (postarg)
                    debug ("postarg: %s", postarg);

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
  if (!output)
    warning("Returned value: (NULL)");
  else
    debug ("output: %s", output);

  return output;
}

#ifdef __cplusplus
}
#endif
