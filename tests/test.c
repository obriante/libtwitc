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

#include <twitc/twitc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pwd.h>

#define PROG_PATH               ".test"
#define CONFIG_DIR              "config"
#define CONFIG_FILE             "Config"
#define PREFERENCE_FILE         "Preference"

#define LOG_FILE	        "/tmp/libtwitc.test.log"

#define TWITTER_KEY             "0xdBqXjFX4LBTLyoc5Dg"
#define TWITTER_KEY_SECRET      "VIr57NPcgxxpJ2esI7brKGhth06EslbH0UDD3ImFB8"

string_t programDir;
string_t configDir;
string_t configFile;

void
initProgramPath()
{
  uid_t uid = geteuid();
  passwd_t *p = getpwuid(uid);

  asprintf(&programDir, "%s/%s", p->pw_dir, PROG_PATH);
  asprintf(&configDir, "%s/%s", programDir, CONFIG_DIR);
  asprintf(&configFile, "%s/%s", configDir, CONFIG_FILE);


  fprintf(stderr, "%s%s\n", "programDir: \t", programDir);




  fprintf(stderr, "%s%s\n", "configDir:\t", configDir);




  fprintf(stderr, "%s%s\n", "configFile:\t", configFile);




}

user_t *
autentication(twitterURLS_t * twURLS, string_t fileName)
{


  fprintf(stderr, "%s%s\n", "twURLS->oauth_URL:\t", twURLS->oauth_URL);




  fprintf(stderr, "%s%s\n", "twURLS->api_URL:\t", twURLS->api_URL);




  fprintf(stderr, "%s%s\n", "twURLS->serch_URL:\t", twURLS->serch_URL);

  if(twURLS->apiFormatType==Json)
    {

      fprintf(stderr, "%s%s\n", "configDir:\t", configDir);



    }
  else{

      fprintf(stderr, "%s%s\n", "configDir:\t", configDir);


  }

  string_t tmpToken = tokenTempBrowser(twURLS, TWITTER_KEY, TWITTER_KEY_SECRET);

  if (tmpToken)
    {


      fprintf(stderr, "%s%s\n", "tmpToken:\t", tmpToken);




      int c;
      char pin[10];
      fprintf(stdout, "inserisci il pin: ");
      fgets(pin, 10, stdin);
      fprintf(stderr, "\n\n%s%s\n", "pin:\t", pin);


      pin[strlen(pin) - 1] = '\0';

      user_t *user = tokenAccess(twURLS, pin, tmpToken);

      //USER CHECK

      if (user)
        {


          fprintf(stderr, "%s%s\n", "user->consumerKey:\t", user->consumerKey);




          fprintf(stderr, "%s%s\n", "user->consumerSecretKey:\t", user->consumerSecretKey);




          fprintf(stderr, "%s%s\n", "user->id:\t", user->id);




          fprintf(stderr, "%s%s\n", "user->screenName:\t", user->screenName);




          fprintf(stderr, "%s%s\n", "user->secretToken:\t", user->secretToken);




          fprintf(stderr, "%s%s\n", "user->token:\t", user->token);



          writeUserFile(user, configFile);

          return user;
        }
    }

  fprintf(stderr,"Returned value: (NULL)\n");
  return NULL ;
}

void
onStatusReading(status_t * status)
{
  if (status->created_at && status->user.screen_name && status->text)
    fprintf(stdout, "\t[%s] @%s: %s\n", status->created_at,
        status->user.screen_name, status->text);
}

void
onTimelineReading(timeline_t * timeline)
{

  int i = 0;
  for (i = 0; i < MAX_NUM_TWEETS; i++)
    {
      if(timeline->statuses[i].text)
        {
          printf("%i)", i + 1);
          onStatusReading(&timeline->statuses[i]);
        }
    }

}

void
onDMReading(direct_message_t * direct_message)
{
  if (direct_message->created_at && direct_message->sender.screen_name && direct_message->recipient.screen_name && direct_message->text)
    fprintf(stdout, "\tDate: %s\nFrom: @%s\nTo: @%s\nMessage: %s\n\n", direct_message->created_at,
        direct_message->sender.screen_name, direct_message->recipient.screen_name, direct_message->text);
}

void onDMsReading(direct_messages_t *DMs)
{
  int i = 0;
  for (i = 0; i < MAX_NUM_DM; i++)
    {
      if(DMs->directMessage[i].text)
        {
          printf("%i)", i + 1);
          onDMReading(&DMs->directMessage[i]);
        }
    }
}


void test(const ApiFormatType_t apiFormatType){

  user_t *user = readUserFile(configFile);

  //OAUTH TEST
  twitterURLS_t *twURLS = initURLS(OAUTH_URL_DEFAULT, API_URL_DEFAULT, SEARCH_URL_DEFAULT, apiFormatType);


  if (!user)
    user = autentication(twURLS, configFile);
  else{
    fprintf(stderr,"user->screenName %s\n",user->screenName);
    fprintf(stderr,"user->id %s\n",user->id);
    fprintf(stderr,"user->consumerKey %s\n",user->consumerKey);
    fprintf(stderr,"user->consumerSecretKey %s\n",user->consumerSecretKey);
    fprintf(stderr,"user->token %s\n",user->token);
    fprintf(stderr,"user->secretToken %s\n",user->secretToken);
  }

  if (user)
    {
      string_t msg=NULL;

      if(apiFormatType==Json)
        msg="Json -Test d'invio tramite libtwitc!";
      else
        msg="Unknown -Test d'invio tramite libtwitc!";


      status_t status = getStatus(updateStatus(twURLS, user, msg));
      onStatusReading(&status);

      timeline_t timeline = readTimeLine(getRawTimeline(twURLS, home_timeline, user));
      onTimelineReading(&timeline);
      uninitTimeline(&timeline);

      direct_messages_t DMs=getDMs(getRawDM(twURLS, user));
      onDMsReading(&DMs);
      uninitDirectMessages(&DMs);

      direct_messages_t sentDMs=getDMs(getRawSentDM(twURLS, user));
      onDMsReading(&sentDMs);
      uninitDirectMessages(&sentDMs);

      string_t dm=sendDM(twURLS, user, user->screenName, msg);


      fprintf(stderr, "%s%s\n", "Direct Message:\t", dm);

      timeline_t favorites = readTimeLine(getRawFavorites(twURLS, user));
      onTimelineReading(&favorites);
      uninitTimeline(&favorites);


      if (user)
        uninitUser(user);

    }

  if (twURLS)
    uninitURLS(twURLS);
}


byte_t
main(int argc, char *argv[])
{

  fprintf(stdout,"start\n");

  initProgramPath();

  //VERSION CHECK

  const char * version = twitc_version();
  const char * copyright = twitc_copyright();

  if (version)
    {
      fprintf(stdout, "\n\nlibtwitc - v%s\n", version);

    }

  if (copyright)
    {
      fprintf(stdout, "%s\n", copyright);

    }

  if (createDirectory(programDir))
    createDirectory(configDir);

  fprintf(stdout,"XML version is deprecated\n");

  test(Json);

  fprintf(stdout,"stop\n");

  return EXIT_SUCCESS;
}
