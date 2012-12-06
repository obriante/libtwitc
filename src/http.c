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
#include <twitc/http.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <curl/curl.h>

#ifdef __cplusplus
extern "C"
{
#endif

string_t fileNameFromUrl(string_t url) {
	string_t filename = NULL;

	filename = strrchr(url, '/');

	if (filename)
		asprintf(&filename, "%s", ++filename);

	return filename;
}

size_t writetoFile(voidPtr_t ptr, size_t size, size_t nmemb, voidPtr_t stream) {
	fwrite(ptr, size, nmemb, (FILE *) stream);

	return nmemb * size;
}
byte_t getFileCURL(string_t url, string_t file) {

	if (url && file) {

		CURL *curl = curl_easy_init();

		if (curl) {

			curl_easy_setopt(curl, CURLOPT_URL, url);
#ifdef DEBUG
			curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
#else
			log(INFO,"Verbose output disabled into the download process");
			curl_easy_setopt(curl, CURLOPT_VERBOSE, false);
#endif
			// Open the file to write the copied file to
			FILE *destFile = fopen(file, "w+b");

			// Tell libcurl where to write the file
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writetoFile);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, destFile);
			curl_easy_perform(curl);

			/*
			 * always cleanup
			 */
			fclose(destFile);
			curl_easy_cleanup(curl);

			return EXIT_SUCCESS;
		}
	}

	return EXIT_FAILURE;
}

typedef struct {
	string_t ptr;
	size_t len;
} dataBuffer_t;

void init_data_buffer(dataBuffer_t * s) {
	s->len = 0;
	s->ptr = malloc(s->len + 1);
	if (s->ptr == NULL ) {
		log(ERROR, "malloc() failed");
		exit(EXIT_FAILURE);
	}
	s->ptr[0] = '\0';
}

size_t writefunc(voidPtr_t ptr, size_t size, size_t nmemb, dataBuffer_t * s) {
	size_t new_len = s->len + size * nmemb;
	s->ptr = realloc(s->ptr, new_len + 1);
	if (s->ptr == NULL ) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(s->ptr + s->len, ptr, size * nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size * nmemb;
}

string_t getPageCURL(string_t url) {
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl) {
		dataBuffer_t s;
		init_data_buffer(&s);

		curl_easy_setopt(curl, CURLOPT_URL, url);
#ifdef DEBUG
		curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
#else
		log(INFO,"Verbose output disabled into the download process");
		curl_easy_setopt(curl, CURLOPT_VERBOSE, false);
#endif
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		res = curl_easy_perform(curl);

		// always cleanup
		curl_easy_cleanup(curl);

		return s.ptr;
	}

	log(WARNING, "Returned value: (NULL)");
	return NULL ;
}

string_t compone_URL(const twitterURLS_t * twURLS,
		const ProtocolType_t protocolType, const string_t urlPath,
		ApiFormatType_t apiFormatType, int api) {
	string_t url = NULL;
	string_t extension = NULL;
	string_t protocol = NULL;

	if(apiFormatType==Xml)
		extension=EXTENSIONFORMAT_XML;
	else if(apiFormatType==Json)
		extension=EXTENSIONFORMAT_JSON;
	else
		extension="\0";

	if (protocolType == Https)
		protocol = PROTOCOL_HTTPS;
	else
		protocol = PROTOCOL_HTTP;

	if (!api)
		asprintf(&url, "%s%s%s%s", protocol, twURLS->oauth_URL, urlPath,
				extension);
	else
		asprintf(&url, "%s%s%s%s", protocol, twURLS->api_URL, urlPath,
				extension);

	if (url)
		debug("url: %s", url);

	return url;
}

string_t componeOAUTH_URL(const twitterURLS_t * twURLS,
		const ProtocolType_t protocolType, const string_t urlPath,
		ApiFormatType_t apiFormatType) {
	return compone_URL(twURLS, protocolType, urlPath, apiFormatType, 0);
}

string_t componeAPI_URL(const twitterURLS_t * twURLS,
		const ProtocolType_t protocolType, const string_t urlPath,
		ApiFormatType_t apiFormatType) {
	return compone_URL(twURLS, protocolType, urlPath, apiFormatType, 1);
}

#ifdef __cplusplus
}
#endif
