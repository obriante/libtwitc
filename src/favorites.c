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


#include <logc/logc.h>

#include <twitc/favorites.h>
#include <twitc/http.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <oauth.h>


string_t getRawFavorites(const twitterURLS_t *twURLS, const user_t *user)
{
  string_t output = NULL;
  string_t url = componeAPI_URL(twURLS, Http, FAVORITESGET_URL, Xml);


  if (url)
     {
       string_t req_url = NULL;
       asprintf(&req_url, "%s%s", url, URL_SEP_QUES);

       if (user)
         req_url = oauth_sign_url2(req_url, NULL, OA_HMAC, NULL,
             user->consumerKey, user->consumerSecretKey, user->token,
             user->secretToken);
       else
         req_url = oauth_sign_url2(req_url, NULL, OA_HMAC, NULL, NULL, NULL,
             NULL, NULL );

       if (req_url)
         {
           debug ("req_url :\t%s", req_url);

           output = oauth_http_get(req_url, NULL );

         }

       if (req_url)
         free(req_url);
       req_url = NULL;
     }

   if (url)
     free(url);
   url = NULL;

   if (!output)
     warning("Returned value: (NULL)");
   else
     debug("output: %s", output);

  return output;
}
