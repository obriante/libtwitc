/* 
 * libtwitc - C Support Library for Twitter
 * Copyright (C) 2012 Orazio Briante orazio.briante@hotmail.it
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
#include <twitc/stdredef.h>
#include <twitc/user.h>

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <libxml/xmlreader.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#ifdef __cplusplus
extern "C"
  {
#endif

user_t *
initUser(string_t id, string_t screenName, string_t token, string_t secretToken,
    string_t consumerKey, string_t consumerSecretKey)
{
  user_t *user = (user_t *) malloc(sizeof(user_t));

  if (user)
    {
      asprintf(&user->id, "%s", id);
      asprintf(&user->screenName, "%s", screenName);
      asprintf(&user->token, "%s", token);
      asprintf(&user->secretToken, "%s", secretToken);
      asprintf(&user->consumerKey, "%s", consumerKey);
      asprintf(&user->consumerSecretKey, "%s", consumerSecretKey);

      debug ("user->id:\t\t\t%s", user->id);debug ("user->screenName:\t\t%s", user->screenName);debug ("user->token:\t\t\t%s", user->token);debug ("user->secretToken:\t\t%s", user->secretToken);debug ("user->consumerKey:\t\t%s", user->consumerKey);debug ("user->consumerSecretKey:\t%s", user->consumerSecretKey);

      return user;
    }

  log(WARNING,"Returned value: (NULL)");
  return NULL ;
}

void
uninitUser(user_t * user)
{

  if (user)
    {
      if (user->id)
        free(user->id);

      if (user->screenName)
        free(user->screenName);

      if (user->token)
        free(user->token);

      if (user->secretToken)
        free(user->secretToken);

      if (user->consumerKey)
        free(user->consumerKey);

      if (user->consumerSecretKey)
        free(user->consumerSecretKey);

      user->consumerKey = NULL;
      user->consumerSecretKey = NULL;
      user->id = NULL;
      user->screenName = NULL;
      user->secretToken = NULL;
      user->token = NULL;

      free(user);

    }

  log(WARNING,"user_t uninitialized");
  user = NULL;
}

void
writeUserFile(const user_t * user, const string_t fileName)
{

  xmlDocPtr doc = xmlNewDoc((xmlChar *) XML_DEFAULT_VERSION);
  xmlNodePtr node = xmlNewDocNode(doc, NULL, (xmlChar *) "CONFIG", NULL );

  xmlDocSetRootElement(doc, node);

  xmlTextWriterPtr writer = xmlNewTextWriterTree(doc, node, 0);

  xmlTextWriterStartDocument(writer, NULL, MY_ENCODING, NULL );

  xmlTextWriterStartElement(writer, (xmlChar *) "USER");
  xmlTextWriterWriteElement(writer, (xmlChar *) "screen_name",
      (xmlChar *) user->screenName);
  xmlTextWriterWriteElement(writer, (xmlChar *) "id", (xmlChar *) user->id);
  xmlTextWriterWriteElement(writer, (xmlChar *) "consumerKey",
      (xmlChar *) user->consumerKey);
  xmlTextWriterWriteElement(writer, (xmlChar *) "consumerSecretKey",
      (xmlChar *) user->consumerSecretKey);
  xmlTextWriterWriteElement(writer, (xmlChar *) "token",
      (xmlChar *) user->token);
  xmlTextWriterWriteElement(writer, (xmlChar *) "secretToken",
      (xmlChar *) user->secretToken);
  xmlTextWriterEndElement(writer);
  xmlTextWriterEndElement(writer);

  xmlFreeTextWriter(writer);

  xmlSaveFileEnc(fileName, doc, MY_ENCODING);

  xmlFreeDoc(doc);

}

user_t *
readUserFile(const string_t fileName)
{

  string_t id;
  string_t screenName;
  string_t token;
  string_t secretToken;
  string_t consumerKey;
  string_t consumerSecretKey;

  xmlDocPtr doc = xmlParseFile(fileName);

  if (doc)
    {

      xmlNodePtr cur = xmlDocGetRootElement(doc);

      if (cur)
        {

          if (!xmlStrcmp(cur->name, (const xmlChar *) "CONFIG"))
            {
              cur = cur->xmlChildrenNode;

              if (cur)
                {

                  if ((!xmlStrcmp(cur->name, (const xmlChar *) "USER")))
                    {

                      cur = cur->xmlChildrenNode;

                      while (cur)
                        {

                          if ((!xmlStrcmp(cur->name,
                              (const xmlChar *) "screen_name")))
                            screenName = xmlNodeListGetString(doc,
                                cur->xmlChildrenNode, 1);

                          else if ((!xmlStrcmp(cur->name,
                              (const xmlChar *) "id")))
                            id = xmlNodeListGetString(doc, cur->xmlChildrenNode,
                                1);

                          else if ((!xmlStrcmp(cur->name,
                              (const xmlChar *) "consumerKey")))
                            consumerKey = xmlNodeListGetString(doc,
                                cur->xmlChildrenNode, 1);

                          else if ((!xmlStrcmp(cur->name,
                              (const xmlChar *) "consumerSecretKey")))
                            consumerSecretKey = xmlNodeListGetString(doc,
                                cur->xmlChildrenNode, 1);

                          else if ((!xmlStrcmp(cur->name,
                              (const xmlChar *) "token")))
                            token = xmlNodeListGetString(doc,
                                cur->xmlChildrenNode, 1);

                          else if ((!xmlStrcmp(cur->name,
                              (const xmlChar *) "secretToken")))
                            secretToken = xmlNodeListGetString(doc,
                                cur->xmlChildrenNode, 1);

                          cur = cur->next;
                        }

                      user_t *user = initUser(id, screenName, token,
                          secretToken, consumerKey, consumerSecretKey);

                      return user;
                    }
                }
            }
        }

      xmlFreeDoc(doc);

    }

  log(WARNING,"Returned value: (NULL)");
  return NULL ;
}

#ifdef __cplusplus
}
#endif
