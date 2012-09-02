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

#include <twitc/twitc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pwd.h>

#define PROG_PATH ".test"
#define CONFIG_DIR "config"
#define CONFIG_FILE "Config"
#define PREFERENCE_FILE "Preference"

#define LOG_FILE	"/tmp/test.log"

#define TWITTER_KEY "0xdBqXjFX4LBTLyoc5Dg"	// USE YOUR APPLICATION KEY
#define TWITTER_KEY_SECRET "VIr57NPcgxxpJ2esI7brKGhth06EslbH0UDD3ImFB8"	// USE YOUR APPLICATION KEY
#define TWC_UPDATES_URL "https://raw.github.com/KernelMonkey/libtwitc/master/VERSION"

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

	debug ("programDir:\t%s", programDir);debug ("configDir:\t%s", configDir);debug ("configFile:\t%s", configFile);

}

user_t *
autentication(twitterURLS_t * twURLS, string_t fileName)
{
	string_t tmpToken = tokenTempBrowser(twURLS, TWITTER_KEY, TWITTER_KEY_SECRET);

	if (tmpToken)
	{
		debug ("tmpToken:\t%s", tmpToken);

		int c;
		char pin[10];
		fprintf(stdout, "inserisci il pin: ");
		fgets(pin, 10, stdin);
		fprintf(stdout, "\n\n");
		debug ("pin:\t%s", pin);

		pin[strlen(pin) - 1] = '\0';

		user_t *user = tokenAccess(twURLS, pin, tmpToken);

		//USER CHECK

		if (user)
		{
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


byte_t
main(int argc, char *argv[])
{

	initLog(FILE_VIDEO_LOG, FILE_VIDEO_LOG);
	openVideoLog(stdout);
	checkFileSize(LOG_FILE, 0);
	openLogFile(LOG_FILE);

	log(INFO,"start");

	initProgramPath();

	//VERSION CHECK

	string_t version = getPageCURL(TWC_UPDATES_URL);

	if (version)
	{
		printf("Version:\t\t%s", version);

		free(version);
		version = NULL;
	}

	if (createDirectory(programDir))
		createDirectory(configDir);

	user_t *user = readUserFile(configFile);

	//OAUTH TEST
	twitterURLS_t *twURLS = initURLS(OAUTH_URL_DEFAULT, API_URL_DEFAULT,
			SEARCH_URL_DEFAULT);

	if (!user)
		user = autentication(twURLS, configFile);

	if (user)
	{
		string_t rawStatus = NULL;

		rawStatus = updateStatus(twURLS, user, "Test d'invio tramite libtwitc!");
		if (rawStatus)
		{
			log(INFO,"Message correctly tweetted!");
			status_t status = getStatus(rawStatus);
			onStatusReading(&status);
		}
		else
			log(INFO,"Message not tweetted!");

		timeline_t timeline = readTimeLine(
				getRawTimeline(twURLS, home_timeline, user));
		onTimelineReading(&timeline);

		uninitTimeline(&timeline);

		string_t rawDM=getRawDM(twURLS, user);
		direct_messages_t DMs=readDMs(rawDM);

		onDMsReading(&DMs);

		uninitDirectMessages(&DMs);


		string_t rawSentDM=getRawSentDM(twURLS, user);
		direct_messages_t sentDMs=readDMs(rawSentDM);

		onDMsReading(&sentDMs);

		uninitDirectMessages(&sentDMs);

		string_t dm=sendDM(twURLS, user, user->screenName,"E' solo un test!");

		log(INFO,"DM: %s", dm);

		timeline_t favorites = readTimeLine(
				getRawFavorites(twURLS, user));

		onTimelineReading(&favorites);

		uninitTimeline(&favorites);


		if (user)
			uninitUser(user);

	}

	if (twURLS)
		uninitURLS(twURLS);

	log(INFO,"stop");

	uninitLog();

	return EXIT_SUCCESS;
}
