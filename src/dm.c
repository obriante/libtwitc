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


#include <twitc/debug.h>
#include <twitc/http.h>
#include <twitc/dm.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <oauth.h>
#include <libxml/xmlreader.h>


#ifdef __cplusplus
extern "C"
{
#endif


  string_t
  _getRawDM(string_t url, const twitterURLS_t * twURLS, const user_t * user)
  {

    string_t output=NULL;

    if (user && twURLS)
      {
        string_t req_url = NULL;
        asprintf(&req_url, "%s%s", url, URL_SEP_QUES);
        req_url = oauth_sign_url2(req_url, NULL, OA_HMAC, NULL, user->consumerKey, user->consumerSecretKey, user->token, user->secretToken);

        if (req_url)
          {
            debug ("req_url :\t%s", req_url);

            output = oauth_http_get(req_url, NULL );

          }

        if (url)
          free(url);
        url = NULL;

        if (req_url)
          free(req_url);
        req_url = NULL;

      }

    if(!output)
      warning("Returned value: (NULL)");

    return output;
  }

  string_t
  getRawDM(const twitterURLS_t * twURLS, const user_t * user)
  {

    string_t url = componeAPI_URL(twURLS, Https, DIRECTMESSAGES_URL, Xml);


    return _getRawDM(url, twURLS, user);
  }


  string_t
  getRawSentDM(const twitterURLS_t * twURLS, const user_t * user)
  {
    string_t url = componeAPI_URL(twURLS, Https, DIRECTMESSAGESSENT_URL, Xml);
    return _getRawDM(url, twURLS, user);
  }


  dm_user_t _getXmlDMUser(const xmlDocPtr doc, xmlNodePtr cur){


    dm_user_t dm_user;
    memset(&dm_user, 0x00, sizeof(dm_user_t));

    while (cur)
      {

        if ((!xmlStrcmp(cur->name, (const xmlChar *) "id")))
          asprintf(&dm_user.id, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "name")))
          asprintf(&dm_user.name, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "screen_name")))
          asprintf(&dm_user.screen_name, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "location")))
          asprintf(&dm_user.location, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "description")))
          asprintf(&dm_user.description, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_image_url")))
          asprintf(&dm_user.profile_image_url, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_image_url_https")))
          asprintf(&dm_user.profile_image_url_https, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "url")))
          asprintf(&dm_user.url, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "protected")))
          asprintf(&dm_user.protected, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "followers_count")))
          asprintf(&dm_user.followers_count, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_background_color")))
          asprintf(&dm_user.profile_background_color, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_text_color")))
          asprintf(&dm_user.profile_text_color, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_link_color")))
          asprintf(&dm_user.profile_link_color, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_sidebar_fill_color")))
          asprintf(&dm_user.profile_sidebar_fill_color, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_sidebar_border_color")))
          asprintf(&dm_user.profile_sidebar_border_color, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "friends_count")))
          asprintf(&dm_user.friends_count, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "created_at")))
          asprintf(&dm_user.created_at, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "favourites_count")))
          asprintf(&dm_user.favourites_count, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "utc_offset")))
          asprintf(&dm_user.utc_offset, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "time_zone")))
          asprintf(&dm_user.time_zone, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_background_image_url")))
          asprintf(&dm_user.profile_background_image_url, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_background_image_url_https")))
          asprintf(&dm_user.profile_background_image_url_https, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_background_tile")))
          asprintf(&dm_user.profile_background_tile, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "profile_use_background_image")))
          asprintf(&dm_user.profile_use_background_image, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "notifications")))
          asprintf(&dm_user.notifications, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "geo_enabled")))
          asprintf(&dm_user.geo_enabled, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "verified")))
          asprintf(&dm_user.verified, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "following")))
          asprintf(&dm_user.following, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "statuses_count")))
          asprintf(&dm_user.statuses_count, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "lang")))
          asprintf(&dm_user.lang, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "contributors_enabled")))
          asprintf(&dm_user.contributors_enabled, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "follow_request_sent")))
          asprintf(&dm_user.follow_request_sent, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "listed_count")))
          asprintf(&dm_user.listed_count, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "show_all_inline_media")))
          asprintf(&dm_user.show_all_inline_media, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "default_profile")))
          asprintf(&dm_user.default_profile, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "default_profile_image")))
          asprintf(&dm_user.default_profile_image, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
        else if ((!xmlStrcmp(cur->name, (const xmlChar *) "is_translator")))
          asprintf(&dm_user.is_translator, "%s",
              xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

        cur = cur->next;
        cur = cur->next;
      }

    return dm_user;
  }


  direct_message_t _getXmlDM(const xmlDocPtr doc, xmlNodePtr cur)
  {
    direct_message_t direct_message;
    memset(&direct_message, 0x00, sizeof(direct_message_t));

    if (cur)
      {
        cur = cur->xmlChildrenNode->next;

        while (cur)
          {
            if ((!xmlStrcmp(cur->name, (const xmlChar *) "id")))
              asprintf(&direct_message.id, "%s",
                  xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
            else if ((!xmlStrcmp(cur->name, (const xmlChar *) "sender_id")))
              asprintf(&direct_message.sender_id, "%s",
                  xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
            else if ((!xmlStrcmp(cur->name, (const xmlChar *) "text")))
              asprintf(&direct_message.text, "%s",
                  xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
            else if ((!xmlStrcmp(cur->name, (const xmlChar *) "recipient_id")))
              asprintf(&direct_message.recipient_id, "%s",
                  xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
            else if ((!xmlStrcmp(cur->name, (const xmlChar *) "created_at")))
              asprintf(&direct_message.created_at, "%s",
                  xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
            else if ((!xmlStrcmp(cur->name, (const xmlChar *) "sender_screen_name")))
              asprintf(&direct_message.sender_screen_name, "%s",
                  xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));
            else if ((!xmlStrcmp(cur->name, (const xmlChar *) "recipient_screen_name")))
              asprintf(&direct_message.recipient_screen_name, "%s",
                  xmlNodeListGetString(doc, cur->xmlChildrenNode, 1));

            else if ((!xmlStrcmp(cur->name, (const xmlChar *) "sender")))
              {

                xmlNodePtr cur2 = cur->xmlChildrenNode->next;

                direct_message.sender=_getXmlDMUser(doc, cur2);

              }

            else if ((!xmlStrcmp(cur->name, (const xmlChar *) "recipient")))
              {

                xmlNodePtr cur2 = cur->xmlChildrenNode->next;


                direct_message.recipient=_getXmlDMUser(doc, cur2);
              }


            cur = cur->next;
            cur = cur->next;
          }

      }

    return direct_message;

  }


  direct_messages_t
  readDMs(const string_t rawDM)
  {

    direct_messages_t direct_messages;
    memset(&direct_messages, 0x00, sizeof(direct_messages));

    if(rawDM){
        xmlDocPtr doc = xmlReadMemory(rawDM, strlen(rawDM), "", NULL,
            XML_PARSE_COMPACT);

        if (doc)
          {
            xmlNodePtr cur = xmlDocGetRootElement(doc);

            while (cur)
              {

                if (!xmlStrcmp(cur->name, (const xmlChar *) "direct-messages"))
                  {

                    debug ("cur->name: %s", cur->name);

                    cur = cur->xmlChildrenNode;

                    int i = 0;
                    while (cur)
                      {
                        if ((!xmlStrcmp(cur->name, (const xmlChar *) "direct_message")))
                          {
                            debug ("cur->name: %s", cur->name);

                            direct_messages.directMessage[i] = _getXmlDM(doc, cur);

                            debug (" %i) [%s] @%s: %s", i,direct_messages.directMessage[i].created_at, direct_messages.directMessage[i].sender_screen_name, direct_messages.directMessage[i].text);
                            i++;
                          }

                        cur = cur->next;

                      }
                  }
              }
          }

        if (doc)
          xmlFreeDoc(doc);
    }

    return direct_messages;
  }



  void
  uninitDMUser(dm_user_t dm_user){

    if(dm_user.id)free(dm_user.id);
    if(dm_user.name)free(dm_user.name);
    if(dm_user.screen_name)free(dm_user.screen_name);
    if(dm_user.location)free(dm_user.location);
    if(dm_user.description)free(dm_user.description);
    if(dm_user.profile_image_url)free(dm_user.profile_image_url);
    if(dm_user.profile_image_url_https)free(dm_user.profile_image_url_https);
    if(dm_user.url)free(dm_user.url);
    if(dm_user.protected)free(dm_user.protected);
    if(dm_user.followers_count)free(dm_user.followers_count);
    if(dm_user.profile_background_color)free(dm_user.profile_background_color);
    if(dm_user.profile_text_color)free(dm_user.profile_text_color);
    if(dm_user.profile_link_color)free(dm_user.profile_link_color);
    if(dm_user.profile_sidebar_fill_color)free(dm_user.profile_sidebar_fill_color);
    if(dm_user.profile_sidebar_border_color)free(dm_user.profile_sidebar_border_color);
    if(dm_user.friends_count)free(dm_user.friends_count);
    if(dm_user.created_at)free(dm_user.created_at);
    if(dm_user.favourites_count)free(dm_user.favourites_count);
    if(dm_user.utc_offset)free(dm_user.utc_offset);
    if(dm_user.time_zone)free(dm_user.time_zone);
    if(dm_user.profile_background_image_url)free(dm_user.profile_background_image_url);
    if(dm_user.profile_background_image_url_https)free(dm_user.profile_background_image_url_https);
    if(dm_user.profile_background_tile)free(dm_user.profile_background_tile);
    if(dm_user.profile_use_background_image)free(dm_user.profile_use_background_image);
    if(dm_user.notifications)free(dm_user.notifications);
    if(dm_user.geo_enabled)free(dm_user.geo_enabled);
    if(dm_user.verified)free(dm_user.verified);
    if(dm_user.following)free(dm_user.following);
    if(dm_user.statuses_count)free(dm_user.statuses_count);
    if(dm_user.lang)free(dm_user.lang);
    if(dm_user.contributors_enabled)free(dm_user.contributors_enabled);
    if(dm_user.follow_request_sent)free(dm_user.follow_request_sent);
    if(dm_user.listed_count)free(dm_user.listed_count);
    if(dm_user.show_all_inline_media)free(dm_user.show_all_inline_media);
    if(dm_user.default_profile)free(dm_user.default_profile);
    if(dm_user.default_profile_image)free(dm_user.default_profile_image);
    if(dm_user.is_translator)free(dm_user.is_translator);;


    dm_user.id=NULL;
    dm_user.name=NULL;
    dm_user.screen_name=NULL;
    dm_user.location=NULL;
    dm_user.description=NULL;
    dm_user.profile_image_url=NULL;
    dm_user.profile_image_url_https=NULL;
    dm_user.url=NULL;
    dm_user.protected=NULL;
    dm_user.followers_count=NULL;
    dm_user.profile_background_color=NULL;
    dm_user.profile_text_color=NULL;
    dm_user.profile_link_color=NULL;
    dm_user.profile_sidebar_fill_color=NULL;
    dm_user.profile_sidebar_border_color=NULL;
    dm_user.friends_count=NULL;
    dm_user.created_at=NULL;
    dm_user.favourites_count=NULL;
    dm_user.utc_offset=NULL;
    dm_user.time_zone=NULL;
    dm_user.profile_background_image_url=NULL;
    dm_user.profile_background_image_url_https=NULL;
    dm_user.profile_background_tile=NULL;
    dm_user.profile_use_background_image=NULL;
    dm_user.notifications=NULL;
    dm_user.geo_enabled=NULL;
    dm_user.verified=NULL;
    dm_user.following=NULL;
    dm_user.statuses_count=NULL;
    dm_user.lang=NULL;
    dm_user.contributors_enabled=NULL;
    dm_user.follow_request_sent=NULL;
    dm_user.listed_count=NULL;
    dm_user.show_all_inline_media=NULL;
    dm_user.default_profile=NULL;
    dm_user.default_profile_image=NULL;
    dm_user.is_translator=NULL;

  }


  void
  uninitDM(direct_message_t direct_message)
  {
    if(direct_message.id)free(direct_message.id);
    if(direct_message.sender_id)free(direct_message.sender_id);
    if(direct_message.text)free(direct_message.text);
    if(direct_message.recipient_id)free(direct_message.recipient_id);
    if(direct_message.created_at)free(direct_message.created_at);
    if(direct_message.sender_screen_name)free(direct_message.sender_screen_name);
    if(direct_message.recipient_screen_name)free(direct_message.recipient_screen_name);

    direct_message.id=NULL;
    direct_message.sender_id=NULL;
    direct_message.text=NULL;
    direct_message.recipient_id=NULL;
    direct_message.created_at=NULL;
    direct_message.sender_screen_name=NULL;
    direct_message.recipient_screen_name=NULL;

    uninitDMUser(direct_message.sender);
    uninitDMUser(direct_message.recipient);
  }

#ifdef __cplusplus
}
#endif
