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
#include <twitc/oauth.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <oauth.h>

#ifdef __cplusplus
extern "C"{
#endif

/*
 *
 *
 * @param oauth_URL
 * @param api_URL
 * @param serch_URL
 * @param apiFormatType
 * @param protocolType
 * @param oauthMethod
 *
 * @return A new allocated twitterURLS_t or NULL if the operation is not possible
 */



twitterURLS_t *initURLS(const string_t oauth_URL, const string_t api_URL, const string_t	serch_URL, const ApiFormatType_t apiFormatType)
{

	if(oauth_URL && api_URL && serch_URL)
	{

		twitterURLS_t *twURLS=(twitterURLS_t *)malloc(sizeof(twitterURLS_t));

		int error=asprintf(&twURLS->api_URL,"%s",api_URL);
		debug("twURLS->api_URL:\t\t\t%s", twURLS->api_URL);

		error=asprintf(&twURLS->oauth_URL,"%s",oauth_URL);
		debug("twURLS->oauth_URL:\t\t\t%s", twURLS->oauth_URL);

		error=asprintf(&twURLS->serch_URL,"%s",serch_URL);
		debug("twURLS->serch_URL:\t\t\t%s", twURLS->serch_URL);

		twURLS->apiFormatType=apiFormatType;

		return twURLS;
	}

	return NULL;
}




/*
 * Send a tweet with User-Keys (token) and TwitCrusader-Keys (token)
 *
 */
string_t sendTweet(const twitterURLS_t *twURLS, const user_t *user, const string_t msg, ApiFormatType_t apiFormatType)
{

	string_t output=NULL;

	if(twURLS && user && msg)
	{
		debug("Message: %s", msg);
		debug("screenName: %s", user->screenName);

		string_t twitterStatusURL=NULL;

		/* Send Tweet with oAuth functions */
		twitterStatusURL=componeAPI_URL(twURLS, Http, STATUSUPDATE_URL, apiFormatType);

		asprintf(&twitterStatusURL,"%s%s%s%s%s", twitterStatusURL, URL_SEP_QUES, "status", "=", oauth_url_escape(msg));

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

				if(postarg)
					debug("postarg: %s", postarg);


				if(sendTweet)
					output = oauth_http_post(sendTweet, postarg);

			}
		}
	}

	if(!output)
		warning("Returned value: (NULL)");
	else
		debug("output: %s", output);

	return output;
}


string_t getTimeline(const string_t timelineURL, const user_t* user )
{

	string_t timeline=NULL;

	if(timelineURL)
	{
		string_t req_url=NULL;
		asprintf(&req_url,"%s%s", timelineURL , URL_SEP_QUES);

		if(user)
			req_url=oauth_sign_url2(req_url, NULL, OA_HMAC, NULL, user->consumerKey, user->consumerSecretKey, user->token, user->secretToken);
		else
			req_url=oauth_sign_url2(req_url, NULL, OA_HMAC, NULL, NULL, NULL, NULL, NULL);


		if(req_url)
		{
			debug("req_url :\t%s", req_url);

			timeline= oauth_http_get(req_url, NULL);

		}
	}


	if(!timeline)
		warning("Returned value: (NULL)");

	return timeline;
}


void uninitURLS(twitterURLS_t *twURLS)
{

	if(twURLS)
	{
		if(twURLS->api_URL)
			free(twURLS->api_URL);

		if(twURLS->oauth_URL)
			free(twURLS->oauth_URL);

		if(twURLS->serch_URL)
			free(twURLS->serch_URL);

		twURLS->api_URL=NULL;
		twURLS->oauth_URL=NULL;
		twURLS->serch_URL=NULL;

		free(twURLS);
	}

	warning("twitterURLS_t uninitialized");
	twURLS=NULL;

}

#ifdef __cplusplus
}
#endif
