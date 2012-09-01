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

#include <logc/logc.h>

#include <twitc/twitter.h>
#include <twitc/user.h>
#include <twitc/http.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <oauth.h>

#ifdef __cplusplus
extern "C"
  {
#endif

twitterURLS_t *
initURLS(const string_t oauth_URL, const string_t api_URL,
    const string_t serch_URL)
{

  if (oauth_URL && api_URL && serch_URL)
    {

      twitterURLS_t *twURLS = (twitterURLS_t *) malloc(sizeof(twitterURLS_t));

      int error = asprintf(&twURLS->api_URL, "%s", api_URL);
      debug ("twURLS->api_URL:\t\t\t%s", twURLS->api_URL);

      error = asprintf(&twURLS->oauth_URL, "%s", oauth_URL);

      debug ("twURLS->oauth_URL:\t\t\t%s", twURLS->oauth_URL);

      error = asprintf(&twURLS->serch_URL, "%s", serch_URL);

      debug ("twURLS->serch_URL:\t\t\t%s", twURLS->serch_URL);

      return twURLS;
    }

  return NULL ;
}

void
uninitURLS(twitterURLS_t * twURLS)
{

  if (twURLS)
    {
      if (twURLS->api_URL)
        free(twURLS->api_URL);

      if (twURLS->oauth_URL)
        free(twURLS->oauth_URL);

      if (twURLS->serch_URL)
        free(twURLS->serch_URL);

      twURLS->api_URL = NULL;
      twURLS->oauth_URL = NULL;
      twURLS->serch_URL = NULL;

      free(twURLS);
    }

  log(WARNING,"twitterURLS_t uninitialized");
  twURLS = NULL;

}

#ifdef __cplusplus
}
#endif
