/***************************************************************************
                          dateformat.h  -  description
                             -------------------
    begin                : dim avr 20 2003
    copyright            : (C) 2003 by Michael CATANZARITI
    email                : mcatan@free.fr
 ***************************************************************************/

/***************************************************************************
 * Copyright (C) The Apache Software Foundation. All rights reserved.      *
 *                                                                         *
 * This software is published under the terms of the Apache Software       *
 * License version 1.1, a copy of which has been included with this        *
 * distribution in the LICENSE.txt file.                                   *
 ***************************************************************************/

#ifndef _LOG4CXX_HELPERS_DATE_FORMAT_H
#define _LOG4CXX_HELPERS_DATE_FORMAT_H

#include <log4cxx/helpers/tchar.h>
#include <log4cxx/helpers/timezone.h>

namespace log4cxx
{
	namespace helpers
	{
		/** 
		Concrete class for formatting and parsing dates in a 
		locale-sensitive manner.
		*/
		class LOG4CXX_EXPORT DateFormat
		{
		public:
			DateFormat(const String& dateFormat);
			DateFormat(const String& dateFormat, const TimeZonePtr& timeZone);
			virtual void format(ostream& os, int64_t time) const;
			String format(int64_t timeMillis) const;

		protected:
			TimeZonePtr timeZone;
			String dateFormat;
		};
	}; // namespace helpers
}; // namespace log4cxx

#endif //_LOG4CXX_HELPERS_DATE_FORMAT_H
