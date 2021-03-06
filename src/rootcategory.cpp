/***************************************************************************
                          rootcategory.cpp  -  description
                             -------------------
    begin                : jeu avr 17 2003
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

#include <log4cxx/spi/rootcategory.h>
#include <log4cxx/helpers/loglog.h>
#include <log4cxx/level.h>
#include <log4cxx/appender.h>

using namespace log4cxx;
using namespace log4cxx::spi;
using namespace log4cxx::helpers;

RootCategory::RootCategory(const Level& level) : Logger(_T("root"))
 {
	setLevel(level);
}

const Level& RootCategory::getEffectiveLevel()
{
	return *level;
}


void RootCategory::setLevel(const Level& level)
{
	if(&level == &Level::OFF)
	{
		LogLog::error(_T("You have tried to set an OFF level to root."));
	}
	else
	{

		this->level = &level;
	}
}



