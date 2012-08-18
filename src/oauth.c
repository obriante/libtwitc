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

#include <twitc/stdredef.h>
#include <twitc/debug.h>
#include <twitc/http.h>
#include <twitc/oauth.h>

#include <oauth.h>

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
	return NULL;
}


string_t
tokenRequest(const twitterURLS_t *twURLS, const string_t c_key, const string_t c_secret)
{

	if(twURLS && c_key && c_secret)
	{

		string_t req_url=componeOAUTH_URL(twURLS, Https, REQTOKEN_URL, None);

		string_t postarg = NULL;
		req_url = oauth_sign_url2(req_url, NULL, OA_HMAC, NULL, c_key, c_secret, NULL, NULL);

		if(postarg)
			debug("postarg: %s", postarg);

		if(req_url)
		{
			debug("req_url:\t%s",req_url);

			string_t tempKeyParameters = oauth_http_get(req_url, postarg);

			if(tempKeyParameters)
			{
				debug("tempKeyParameters:\t%s",tempKeyParameters);

				return tempKeyParameters;
			}
		}
	}

	warning("Returned value: (NULL)");
	return NULL;

}



/*
 * Main function for oAuth access
 *
 * Authorize Twitter Account
 *
 */
string_t
tokenTemp(const twitterURLS_t * twURLS, const string_t twitterKey, const string_t twitterKeySecret)
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
				string_t cmd=NULL;
				string_t url=NULL;

				string_t req_url=componeOAUTH_URL(twURLS, Https, AUTHORIZE_URL, None);

				asprintf(&url,"%s%s%s%s%s", req_url, URL_SEP_QUES, "oauth_token","=",tempKey);

				asprintf(&cmd, "xdg-open \"%s\"", url);
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
			string_t accessURL=componeOAUTH_URL(twURLS, Https, ACCESS_TOKEN_URL, None);

			asprintf(&accessURL,"%s%s%s%s%s", accessURL, URL_SEP_QUES, "oauth_verifier","=",pin);

			if(accessURL)
			{
				debug("accessURL:\t%s", accessURL);
				string_t postarg = NULL;
				string_t verifyPIN = oauth_sign_url2(accessURL, &postarg, OA_HMAC, NULL, consumerKey, consumerSecretKey, tempKey, tempKeySecret);

				if(postarg)
					debug("postarg: %s", postarg);

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
