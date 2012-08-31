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

#include <twitc/stdredef.h>
#include <twitc/functions.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
  {
#endif

byte_t
createDirectory(string_t dirName)
{

  if (dirName)
    {
      if (mkdir(dirName, 0777))
        return EXIT_SUCCESS;

    }

  return EXIT_FAILURE;

}

string_t
readRawTextFile(const string_t fileName)
{
  if (fileName)
    {
      FILE *fp = fopen(fileName, "r");

      if (fp)
        {

          fseek(fp, 0L, SEEK_END);
          int sz = ftell(fp);
          rewind(fp);

          string_t buffer = (string_t) malloc(sz);

          fread(buffer, sz, 1, fp);
          fclose(fp);

          return buffer;
        }

    }

  warning("Returned value: (NULL)");
  return NULL ;
}

byte_t
initFileLock(const string_t fileName)
{
  if (fileName)
    {

      FILE *fp = fopen(fileName, "r");

      if (!fp)
        {
          fp = fopen(fileName, "w");

          if (fp)
            {
              fclose(fp);
              return EXIT_SUCCESS;
            }

        }
      else
        fclose(fp);
    }

  return EXIT_FAILURE;
}

#ifdef __cplusplus
}
#endif
