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

#include "logc/include/logc/logc.h"

#include <twitc/twitc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pwd.h>

#define PROG_PATH ".test"
#define CONFIG_DIR "config"
#define CONFIG_FILE "Config"
#define PREFERENCE_FILE "Preference"

#define LOG_FILE	"/tmp/libtwitc.test.log"

#define TWITTER_KEY "0xdBqXjFX4LBTLyoc5Dg"
#define TWITTER_KEY_SECRET "VIr57NPcgxxpJ2esI7brKGhth06EslbH0UDD3ImFB8"

#define TWC_UPDATES_URL "https://raw.github.com/KernelMonkey/libtwitc/master/VERSION"

string_t programDir;
string_t configDir;
string_t configFile;

string_t debug=NULL;

void
initProgramPath()
{
	uid_t uid = geteuid();
	passwd_t *p = getpwuid(uid);

	asprintf(&programDir, "%s/%s", p->pw_dir, PROG_PATH);
	asprintf(&configDir, "%s/%s", programDir, CONFIG_DIR);
	asprintf(&configFile, "%s/%s", configDir, CONFIG_FILE);

	debug=NULL;
	asprintf(&debug, "%s%s", "programDir: \t", programDir);
	log(DEBUG,debug);
	free(debug);

	debug=NULL;
	asprintf(&debug, "%s%s", "configDir:\t", configDir);
	log(DEBUG,debug);
	free(debug);

	debug=NULL;
	asprintf(&debug, "%s%s", "configFile:\t", configFile);
	log(DEBUG,debug);
	free(debug);


}

user_t *
autentication(twitterURLS_t * twURLS, string_t fileName)
{

	debug=NULL;
	asprintf(&debug, "%s%s", "twURLS->oauth_URL:\t", 	twURLS->oauth_URL);
	log(DEBUG,debug);
	free(debug);

	debug=NULL;
	asprintf(&debug, "%s%s", "twURLS->api_URL:\t", twURLS->api_URL);
	log(DEBUG,debug);
	free(debug);

	debug=NULL;
	asprintf(&debug, "%s%s", "twURLS->serch_URL:\t", twURLS->serch_URL);
	log(DEBUG,debug);
	free(debug);


	if(twURLS->apiFormatType==Xml)
	{
		debug=NULL;
		asprintf(&debug, "%s%s", "configDir:\t", configDir);
		log(DEBUG,debug);
		free(debug);

	}
	else if(twURLS->apiFormatType==Json)
	{
		debug=NULL;
		asprintf(&debug, "%s%s", "configDir:\t", configDir);
		log(DEBUG,debug);
		free(debug);

	}
	else{
		debug=NULL;
		asprintf(&debug, "%s%s", "configDir:\t", configDir);
		log(DEBUG,debug);
		free(debug);
	}

	string_t tmpToken = tokenTempBrowser(twURLS, TWITTER_KEY, TWITTER_KEY_SECRET);

	if (tmpToken)
	{

		debug=NULL;
		asprintf(&debug, "%s%s", "tmpToken:\t", tmpToken);
		log(DEBUG,debug);
		free(debug);


		int c;
		char pin[10];
		fprintf(stdout, "inserisci il pin: ");
		fgets(pin, 10, stdin);
		fprintf(stdout, "\n\n");

		debug=NULL;
		asprintf(&debug, "%s%s", "pin:\t", pin);
		log(DEBUG,debug);
		free(debug);

		pin[strlen(pin) - 1] = '\0';

		user_t *user = tokenAccess(twURLS, pin, tmpToken);

		//USER CHECK

		if (user)
		{

			debug=NULL;
			asprintf(&debug, "%s%s", "user->consumerKey:\t", user->consumerKey);
			log(DEBUG,debug);
			free(debug);

			debug=NULL;
			asprintf(&debug, "%s%s", "user->consumerSecretKey:\t", user->consumerSecretKey);
			log(DEBUG,debug);
			free(debug);

			debug=NULL;
			asprintf(&debug, "%s%s", "user->id:\t", user->id);
			log(DEBUG,debug);
			free(debug);

			debug=NULL;
			asprintf(&debug, "%s%s", "user->screenName:\t", user->screenName);
			log(DEBUG,debug);
			free(debug);

			debug=NULL;
			asprintf(&debug, "%s%s", "user->secretToken:\t", user->secretToken);
			log(DEBUG,debug);
			free(debug);

			debug=NULL;
			asprintf(&debug, "%s%s", "user->token:\t", user->token);
			log(DEBUG,debug);
			free(debug);

			writeUserFile(user, configFile);

			return user;
		}
	}
	log(WARNING,"Returned value: (NULL)");
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

	if (user)
	{
		string_t msg=NULL;

		if(apiFormatType==Json)
			msg="Json -Test d'invio tramite libtwitc!";
		else if(apiFormatType==Xml)
			msg="Xml -Test d'invio tramite libtwitc!";
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

		debug=NULL;
		asprintf(&debug, "%s%s", "Direct Message:\t", dm);
		log(DEBUG,debug);
		free(debug);

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

	initLog(FILE_VIDEO_LOG, FILE_VIDEO_LOG);
	openVideoLog(stderr);
	checkFileSize(LOG_FILE, 0);
	openLogFile(LOG_FILE);

	log(INFO,"start");

	initProgramPath();

	//VERSION CHECK

	string_t version = getPageCURL(TWC_UPDATES_URL);

	if (version)
	{
		fprintf(stdout, "Version:\t\t%s", version);

		free(version);
		version = NULL;
	}

	if (createDirectory(programDir))
		createDirectory(configDir);

	//test(Xml);

	info("XML version is deprecated");

	test(Json);

	log(INFO,"stop");

	uninitLog();

	return EXIT_SUCCESS;
}
