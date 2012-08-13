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
#include <twitc/twitter.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pwd.h>

#define		PROG_PATH				".test"
#define		CONFIG_DIR				"config"
#define		CONFIG_FILE				"Config"
#define		PREFERENCE_FILE			"Preference"

#define		TWITTER_KEY			"" // USE YOUR APPLICATION KEY
#define		TWITTER_KEY_SECRET		"" // USE YOUR APPLICATION KEY

#define		TWC_UPDATES_URL			"https://raw.github.com/KernelMonkey/libtwitc/master/VERSION"

#define		OAUTH_API_URL_DEFAULT	"https://api.twitter.com/oauth/"
#define		HTTPS_API_URL_DEFAULT	"https://api.twitter.com/1/"

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

	initLog("/tmp/test.log", high, 1024);
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
	twitterURLS_t *twURLS=initURLS(OAUTH_API_URL_DEFAULT, HTTPS_API_URL_DEFAULT);


	if(!user)
		user=autentication(twURLS, configFile);


	if(user)
	{
		string_t rawTimeline=getTimeline(twURLS->home_timeline_url, user );

		// debug("rawTimeline:\n\n%s",rawTimeline);


		timeline_t timeline=readTimeLine(rawTimeline);

		onTimelineReading(&timeline);

		string_t msg="Test d'invio tramite libtwitc..";
		info("Tweet: %s", msg);

		if(!sendTweet(twURLS, user, msg))
			info("Message correctly tweetted!");
		else
			info("Message not tweetted!");

		if(user)
			uninitUser(user);

	}



	info("stop");

	uninitLog();

	return EXIT_SUCCESS;
}
