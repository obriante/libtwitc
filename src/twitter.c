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
#include <twitc/twitter.h>
#include <twitc/user.h>
#include <twitc/http.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <oauth.h>

#ifdef __cplusplus
extern "C"{
#endif

twitterURLS_t *initURLS(const string_t oauth_API_URL, const string_t https_API_URL)
{

	twitterURLS_t *twURLS=(twitterURLS_t *)malloc(sizeof(twitterURLS_t));

	int error=asprintf(&twURLS->authorize_url,"%s%s",oauth_API_URL,"authorize");
	debug("twURLS->authorize_url:\t\t\t%s", twURLS->authorize_url);

	error=asprintf(&twURLS->request_url,"%s%s",oauth_API_URL,"request_token");
	debug("twURLS->request_url:\t\t\t%s", twURLS->request_url);

	error=asprintf(&twURLS->tokenaccess_url,"%s%s",oauth_API_URL, "access_token");
	debug("twURLS->tokenaccess_url:\t\t%s", twURLS->tokenaccess_url);

	error=asprintf(&twURLS->status_url,"%s%s",https_API_URL,"statuses/update.xml?status=");
	debug("twURLS->status_url:\t\t\t%s", twURLS->status_url);

	error=asprintf(&twURLS->home_timeline_url,"%s%s",https_API_URL,"statuses/home_timeline.xml");
	debug("twURLS->home_timeline_url:\t\t%s", twURLS->home_timeline_url);

	error=asprintf(&twURLS->public_timeline_url,"%s%s",https_API_URL,"statuses/public_timeline.xml");
	debug("twURLS->public_timeline_url:\t\t%s", twURLS->public_timeline_url);

	error=asprintf(&twURLS->mentions_timeline_url,"%s%s",https_API_URL,"statuses/mentions.xml");
	debug("twURLS->mentions_timeline_url:\t\t%s", twURLS->mentions_timeline_url);

	error=asprintf(&twURLS->friends_timeline_url,"%s%s",https_API_URL,"statuses/friends_timeline.xml");
	debug("twURLS->friends_timeline_url:\t\t%s", twURLS->friends_timeline_url);

	error=asprintf(&twURLS->user_timeline_url,"%s%s",https_API_URL,"statuses/user_timeline.xml");
	debug("twURLS->user_timeline_url:\t\t%s", twURLS->user_timeline_url);

	error=asprintf(&twURLS->rt_by_me_timeline_url,"%s%s",https_API_URL,"statuses/retweeted_by_me.xml");
	debug("twURLS->rt_by_me_timeline_url:\t\t%s", twURLS->rt_by_me_timeline_url);

	error=asprintf(&twURLS->rt_to_me_timeline_url,"%s%s",https_API_URL,"statuses/retweeted_to_me.xml");
	debug("twURLS->rt_to_me_timeline_url:\t\t%s", twURLS->rt_to_me_timeline_url);

	error=asprintf(&twURLS->rt_of_me_timeline_url,"%s%s",https_API_URL,"statuses/retweeted_of_me.xml");
	debug("twURLS->rt_of_me_timeline_url:\t\t%s", twURLS->rt_of_me_timeline_url);

	return twURLS;
}

/*
 * This function split url-parameters with delimiter char
 * WARINING: use it with oauth_split_url_parameters() for variables rv
 *
 * Exemple:
 * param = oauth_token
 * rc = 1
 * rv = oauth=XXXXXXXXXX&token=ZZZZZZZZZ
 * Return = XXXXXXXXXX
 *
 */
string_t getParameters(string_t argv[], int argc, const string_t param) //Improved by freddy
{

	if(argv && argc && param)
	{
		int i=0;

		for(i = 0; i < argc; i++)
		{
			if(!strncmp(argv[i],param,strlen(param)))
				return (argv[i] + strcspn(argv[i],"=") + 1);

		}
	}

	warning("Returned value: (NULL)");
	warning("Returned value: (NULL)");
	return NULL;
}


/*
 * This function generate a 2 Twitter-Temp-Key
 * Use this Temp-keys for generate a PIN
 * Use PIN and Twitter-Temp-Keys for validate a correct PIN
 *
 * @Return Url-Parameters with Consumer-Temp-Key and Consumer-Temp-Key-Secret
 *
 */
string_t tokenRequest(const twitterURLS_t *twURLS, const string_t consumerKey, const string_t consumerKeySecret)
{
	if(twURLS && consumerKey && consumerKeySecret)
	{
		string_t postarg = NULL;

		/* Generate a request url, this url have Temp-Key */
		string_t twitterRequestURL = oauth_sign_url2(twURLS->request_url, NULL, OA_HMAC, NULL, consumerKey, consumerKeySecret, NULL, NULL);
		if(twitterRequestURL)
		{
			debug("twitterRequestURL:\t%s",twitterRequestURL);

			string_t tempKeyParameters = oauth_http_get(twitterRequestURL, postarg);
			if(tempKeyParameters)
			{
				debug("tempKeyParameters:\t%s",tempKeyParameters);

				return tempKeyParameters;
			}
		}
	}

	warning("Returned value: (NULL)");
	warning("Returned value: (NULL)");
	return NULL;
}

/*
 * Main function for oAuth access
 *
 * Authorize Twitter Account
 *
 */
string_t tokenTempBrowser(const twitterURLS_t * twURLS, const string_t twitterKey, const string_t twitterKeySecret )
{

	int rc;
	string_t *rv=NULL;

	/*
	 * @Input: TwitCrusader Consumer-Key
	 * @Return Url-Parameters with Consumer-Temp-Key and Consumer-Temp-Key-Secret
	 *
	 */
	string_t tempKeyURL = tokenRequest(twURLS, twitterKey, twitterKeySecret);

	if(tempKeyURL)
	{
		debug("tempKeyURL:\t%s",tempKeyURL);

		/* split url and get Temp-Key */
		rc = oauth_split_url_parameters(tempKeyURL, &rv);
		string_t tempKey = getParameters(rv, rc, "oauth_token");

		if(tempKey)
		{
			debug("tempKey:\t%s",tempKey);

			/*
			 * Save all Twitter-Key at /tmp folder
			 * Temp-Key + Temp-Key-Secret + TwitCrusader Key + TwitCrusader Key Secret
			 */
			char* tmpToken;

			asprintf(&tmpToken, "%s%s%s%s%s", tempKeyURL, "&c_key=", twitterKey, "&c_key_secret=", twitterKeySecret);

			if(tmpToken)
			{
				debug("tmpToken:\t%s",tmpToken);

				/* Generate a Twitter-URL for get user-PIN */
				char* cmd;
				asprintf(&cmd, "xdg-open \"%s?oauth_token=%s\"", twURLS->authorize_url, tempKey);
				if(cmd)
				{
					debug("cmd:\t%s", cmd);

					/* Open URL and user get PIN */
					system(cmd);

					return tmpToken;
				}
			}
		}
	}

	warning("Returned value: (NULL)");
	warning("Returned value: (NULL)");
	return NULL;
}

/*
 * Main function for oAuth access
 *
 * Authorize Twitter Account
 *
 */
string_t tokenTemp(const twitterURLS_t * twURLS, const string_t twitterKey, const string_t twitterKeySecret)
{

	int rc;
	string_t *rv=NULL;

	/*
	 * @Input: TwitCrusader Consumer-Key
	 * @Return Url-Parameters with Consumer-Temp-Key and Consumer-Temp-Key-Secret
	 *
	 */
	string_t tempKeyURL = tokenRequest(twURLS, twitterKey, twitterKeySecret);

	if(tempKeyURL)
	{
		debug("tempKeyURL:\t%s", tempKeyURL);

		/* split url and get Temp-Key */
		rc = oauth_split_url_parameters(tempKeyURL, &rv);
		string_t tempKey = getParameters(rv, rc, "oauth_token");

		if(tempKey)
		{
			debug("tempKey:\t%s", tempKey);

			/*
			 * Save all Twitter-Key at /tmp folder
			 * Temp-Key + Temp-Key-Secret + TwitCrusader Key + TwitCrusader Key Secret
			 */
			string_t tmpToken;
			asprintf(&tmpToken, "%s%s%s%s%s", tempKeyURL, "&c_key=", twitterKey, "&c_key_secret=", twitterKeySecret);
			if(tmpToken)
			{
				debug("tmpToken:\t%s", tmpToken);

				return tmpToken;
			}
		}
	}
	warning("Returned value: (NULL)");
	return NULL;
}

/*
 * Validate a PIN with Temp-Key and save all user-info
 *
 * @Return User-Key, User-Secret-Key, Username, User-ID and other
 * All info is saved at ~/.twc/config/user file
 *
 */
user_t *tokenAccess(const twitterURLS_t *twURLS, const string_t pin, const string_t tmpToken)
{

	string_t *rv=NULL;

	debug("tmpToken:\t%s", tmpToken);
	debug("pin:\t%s", pin);

	if(twURLS && pin && tmpToken)
	{
		debug("tmpToken:\t%s", tmpToken);
		debug("pin:\t%s", pin);

		int rc = oauth_split_url_parameters(tmpToken, &rv);

		string_t tempKey=getParameters(rv, rc, "oauth_token");
		string_t tempKeySecret=getParameters(rv, rc, "oauth_token_secret");
		string_t consumerKey=getParameters(rv, rc, "c_key");
		string_t consumerSecretKey=getParameters(rv, rc, "c_key_secret");

		if(tempKey && tempKeySecret && consumerKey && consumerSecretKey)
		{
			debug("tempKey:\t%s", tempKey);
			debug("tempKeySecret:\t%s", tempKeySecret);
			debug("consumerKey:\t%s", consumerKey);
			debug("consumerSecretKey:\t%s:", consumerSecretKey);

			/* Generate a URL, this verify a PIN
			 * For validate PIN is necessary: TwitCrusader consumer key (and secret) with a 2 Temp-Keys
			 * All keys are saved in /tmp/token file
			 */
			string_t accessURL;
			asprintf(&accessURL, "%s?oauth_verifier=%s", twURLS->tokenaccess_url, pin);

			if(accessURL)
			{
				debug("accessURL:\t%s", accessURL);
				string_t postarg = NULL;
				string_t verifyPIN = oauth_sign_url2(accessURL, &postarg, OA_HMAC, NULL, consumerKey, consumerSecretKey, tempKey, tempKeySecret);
				string_t twitterUserKey = oauth_http_post(verifyPIN,postarg);

				debug("twitterUserKey:\t%s", twitterUserKey);

				if (twitterUserKey)
				{

					/* Split all parameters and get User-ID, Username, and User-Keys */
					rc = oauth_split_url_parameters(twitterUserKey, &rv);

					string_t token=getParameters(rv, rc, "oauth_token");
					string_t secretToken=getParameters(rv, rc, "oauth_token_secret");
					string_t id=getParameters(rv, rc, "user_id");
					string_t screenName=getParameters(rv, rc, "screen_name");

					if(token && secretToken && id && screenName)
					{
						/*DEBUG*/
						debug("screenName:\t%s",screenName);
						debug("id:\t%s",id);
						debug("consumerKey:\t%s", consumerKey);
						debug("consumerSecretKey:\t%s", consumerSecretKey);
						debug("token:\t%s", token);
						debug("secretToken:\t%s", secretToken);


						user_t *user=initUser(id, screenName, token, secretToken, consumerKey, consumerSecretKey);

						return user;
					}
				}
			}
		}
	}

	warning("Returned value: (NULL)");
	return NULL;
}

/*
 * Send a tweet with User-Keys (token) and TwitCrusader-Keys (token)
 *
 */
byte_t sendTweet(const twitterURLS_t *twURLS, const user_t *user, const string_t msg)
{

	if(twURLS && user && msg)
	{

	debug("twURLS->status_url: %s",twURLS->status_url);
        debug("Message: %s", msg);
        debug("screenName: %s", user->screenName);


		string_t twitterStatusURL;
		/* Send Tweet with oAuth functions */
		asprintf(&twitterStatusURL, "%s%s",  twURLS->status_url, oauth_url_escape(msg));

		if(twitterStatusURL)
		{
			debug("twitterStatusURL:\t%s", twitterStatusURL);


			if(user->id && user->screenName && user->consumerKey && user->consumerSecretKey && user->token && user->secretToken)
			{

				/*DEBUG*/
				debug("user->screenName:\t%s",user->screenName);
				debug("user->id",user->id);
				debug("user->consumerKey",user->consumerKey);
				debug("user->consumerSecretKey",user->consumerSecretKey);
				debug("user->token",user->token);
				debug("user->secretToken",user->secretToken);

				string_t postarg = NULL;
				string_t sendTweet = oauth_sign_url2(twitterStatusURL, &postarg, OA_HMAC, NULL, user->consumerKey, user->consumerSecretKey, user->token, user->secretToken);
				if(sendTweet)
				{

					string_t error = oauth_http_post(sendTweet, postarg);
					if(!error)
						return EXIT_FAILURE;

					return EXIT_SUCCESS;


				}
			}
		}
	}

	return EXIT_FAILURE;
}


string_t getTimeline(const string_t timelineURL, const user_t* user )
{


	string_t url=oauth_sign_url2(timelineURL, NULL, OA_HMAC, NULL, user->consumerKey, user->consumerSecretKey, user->token, user->secretToken);

	if(url)
	{
		debug("Timeline URL:\t%s", url);

		char*postarg=NULL;
		string_t timeline= oauth_http_get(url, postarg);

		if(timeline)
		{

			return timeline;
		}
	}


	warning("Returned value: (NULL)");
	return NULL;
}

#ifdef __cplusplus
}
#endif
