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


#include <logc/logc.h>

#include <twitc/http.h>
#include <twitc/status.h>
#include <twitc/user.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <oauth.h>
#include <libxml/xmlreader.h>


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

    debug("twitterUser_t correctly uninitialized");

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

    debug("status_t correctly uninitialized");
  }


#ifdef __cplusplus
}
#endif

