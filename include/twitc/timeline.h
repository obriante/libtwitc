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

#ifndef TIMELINE_H_
#define TIMELINE_H_

#include <twitc/stdredef.h>
#include <twitc/status.h>
#include <twitc/twitter.h>

#define		MAX_NUM_TWEETS	20

typedef enum
{
  home_timeline,
  public_timeline,
  featured,
  friends_timeline,
  mentions,
  user_timeline
} timelineType_t;

typedef struct
{
  status_t statuses[MAX_NUM_TWEETS];
  timelineType_t type;
} timeline_t;



extern string_t
getRawTimeline(const twitterURLS_t *, timelineType_t, const user_t *, const ApiFormatType_t apiFormatType);

extern timeline_t
readTimeLine(const string_t);

extern void uninitTimeline(timeline_t *);


#endif /* TIMELINE_H_ */
