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

#include <twitc/debug.h>
#include <twitc/stdredef.h>
#include <twitc/functions.h>
#include <twitc/user.h>
#include <twitc/timeline.h>
#include <twitc/http.h>
#include <twitc/oauth.h>
#include <twitc/twitter.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pwd.h>

#define		PROG_PATH				".test"
#define		CONFIG_DIR				"config"
#define		CONFIG_FILE				"Config"
#define		PREFERENCE_FILE			"Preference"

#define		TWITTER_KEY					"0xdBqXjFX4LBTLyoc5Dg"	// USE YOUR APPLICATION KEY
#define		TWITTER_KEY_SECRET			"VIr57NPcgxxpJ2esI7brKGhth06EslbH0UDD3ImFB8" // USE YOUR APPLICATION KEY

#define		TWC_UPDATES_URL			"https://raw.github.com/KernelMonkey/libtwitc/master/VERSION"

string_t programDir;
string_t configDir;
string_t configFile;


void initProgramPath()
{
	uid_t uid = geteuid();
	passwd_t *p= getpwuid(uid);

	asprintf(&programDir, "%s/%s", p->pw_dir,PROG_PATH);
	asprintf(&configDir, "%s/%s", programDir,CONFIG_DIR);
	asprintf(&configFile, "%s/%s",configDir,CONFIG_FILE);


	debug("programDir:\t%s",programDir);
	debug("configDir:\t%s",configDir);
	debug("configFile:\t%s",configFile);

}


user_t *autentication(twitterURLS_t *twURLS, string_t fileName)
{
	string_t tmpToken=tokenTempBrowser(twURLS, TWITTER_KEY, TWITTER_KEY_SECRET);

	if(tmpToken)
	{
		debug("tmpToken:\t%s",tmpToken);

		int c;
		char pin[10];
		fprintf(stdout, "inserisci il pin: ");
		fgets(pin, 10, stdin);
		fprintf(stdout, "\n\n");
		debug("pin:\t%s", pin);

		pin[strlen(pin)-1]='\0';


		user_t *user=tokenAccess(twURLS, pin, tmpToken);


		//USER CHECK

		if(user)
		{
			writeUserFile(user,configFile);

			return user;
		}
	}
	warning("Returned value: (NULL)");
	return NULL;
}


byte_t onTimelineReading(timeline_t *timeline){

	int i=0;
	for(i=0; i<MAX_NUM_TWEETS; i++)
	{
		if(timeline->timeline[i].created_at && timeline->timeline[i].user.screen_name && timeline->timeline[i].text)
			fprintf(stdout,"%i)\t[%s] @%s: %s\n", i+1, timeline->timeline[i].created_at, timeline->timeline[i].user.screen_name, timeline->timeline[i].text);


	}

	return EXIT_SUCCESS;
}

byte_t main(int argc, char *argv[])
{

	initLog("/tmp/test.log", (1024*1000));
	info("start");

	initProgramPath();

	//VERSION CHECK

	string_t  version=getPageCURL(TWC_UPDATES_URL);

	if(version)
	{
		printf("Version:\t\t%s", version);

		free(version);
		version=NULL;
	}


	if(createDirectory(programDir))
		createDirectory(configDir);

	user_t *user=readUserFile(configFile);


	//OAUTH TEST
	twitterURLS_t *twURLS=initURLS(OAUTH_URL_DEFAULT, API_URL_DEFAULT, SEARCH_URL_DEFAULT, Xml);


	if(!user)
		user=autentication(twURLS, configFile);


	if(user)
	{

		if(sendTweet(twURLS, user, "Test d'invio tramite libtwitc usando Xml", Xml))
			info("XML Message correctly tweetted!");
		else
			info("XML Message not tweetted!");

		if(sendTweet(twURLS, user, "Test d'invio tramite libtwitc usando Json", Json))
			info("Json Message correctly tweetted!");
		else
			info("Json Message not tweetted!");


		string_t url=componeAPI_URL(twURLS, Http, HOME_TIMELINE_URL, Xml);

		timeline_t TimelineXml=readXmlTimeLine(getTimeline(url, user ));
		onTimelineReading(&TimelineXml);

		url=componeAPI_URL(twURLS, Http, HOME_TIMELINE_URL, Json);

		timeline_t TimelineJson=readJsonTimeLine(getTimeline(url, user));
		onTimelineReading(&TimelineJson);


		if(user)
			uninitUser(user);

	}


	if(twURLS)uninitURLS(twURLS);

	info("stop");

	uninitLog();

	return EXIT_SUCCESS;
}
