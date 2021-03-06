/***************************************************************************
                          asyncappender.h  -  AsyncAppender
                             -------------------
    begin                : sam mai 17 2003
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

#ifndef _LOG4CXX_ASYNC_APPENDER_H
#define _LOG4CXX_ASYNC_APPENDER_H

#include <log4cxx/appenderskeleton.h>
#include <log4cxx/helpers/appenderattachableimpl.h>
#include <log4cxx/helpers/thread.h>

namespace log4cxx
{
	namespace helpers
	{
		class BoundedFIFO;
		typedef ObjectPtr<BoundedFIFO> BoundedFIFOPtr;
	};

	class Dispatcher;
	
	/**
	The AsyncAppender lets users log events asynchronously. It uses a
	bounded buffer to store logging events.

	<p>The AsyncAppender will collect the events sent to it and then
	dispatch them to all the appenders that are attached to it. You can
	attach multiple appenders to an AsyncAppender.

	<p>The AsyncAppender uses a separate thread to serve the events in
	its bounded buffer.

	<p><b>Important note:</b> The <code>AsyncAppender</code> can only
	be script configured using the {@link xml::DOMConfigurator DOMConfigurator}.
	*/
	class AsyncAppender :
		public AppenderSkeleton,
		public helpers::AppenderAttachableImpl
	{
	friend class Dispatcher;

	public:
		/** The default buffer size is set to 128 events. */
		static int DEFAULT_BUFFER_SIZE;

		helpers::BoundedFIFOPtr bf;
		Dispatcher * dispatcher;
		bool locationInfo;
		bool interruptedWarningMessage;

		AsyncAppender();
		~AsyncAppender();

		void append(const spi::LoggingEvent& event);

		/**
		Close this <code>AsyncAppender</code> by interrupting the
		dispatcher thread which will process all pending events before
		exiting.
		*/
		void close();

		/**
		Returns the current value of the <b>LocationInfo</b> option.
		*/
		inline bool getLocationInfo() const
			{ return locationInfo; }

		/**
		The <code>AsyncAppender</code> does not require a layout. Hence,
		this method always returns <code>false</code>.
		*/
		virtual bool requiresLayout()
			{ return false; }

		/**
		* The <b>LocationInfo</b> option takes a boolean value. By default,
		* it is set to false which means there will be no effort to extract
		* the location information related to the event. As a result, the
		* event that will be ultimately logged will likely to contain the
		* wrong location information (if present in the log format).
		*
		* <p>Location information extraction is comparatively very slow and
		* should be avoided unless performance is not a concern.
		* */
		inline void setLocationInfo(bool flag)
			{ locationInfo = flag; }

		/**
		* The <b>BufferSize</b> option takes a non-negative integer value.
		* This integer value determines the maximum size of the bounded
		* buffer. Increasing the size of the buffer is always
		* safe. However, if an existing buffer holds unwritten elements,
		* then <em>decreasing the buffer size will result in event
		* loss.</em> Nevertheless, while script configuring the
		* AsyncAppender, it is safe to set a buffer size smaller than the
		* {@link #DEFAULT_BUFFER_SIZE default buffer size} because
		* configurators guarantee that an appender cannot be used before
		* being completely configured.
		* */
		void setBufferSize(int size);

		/**
		Returns the current value of the <b>BufferSize</b> option.
		*/
		int getBufferSize();
	}; // class AsyncAppender

	class Dispatcher : public  helpers::Thread
	{
		helpers::BoundedFIFOPtr bf;
		bool interrupted;
		AsyncAppender * container;

	public:
		Dispatcher(helpers::BoundedFIFOPtr bf, AsyncAppender * container);
		void close();

		/**
		The dispatching strategy is to wait until there are events in the
		buffer to process. After having processed an event, we release
		the monitor (variable bf) so that new events can be placed in the
		buffer, instead of keeping the monitor and processing the remaining
		events in the buffer.
		<p>Other approaches might yield better results.
		*/
		void run();
	}; // class Dispatcher
}; //  namespace log4cxx

#endif//  _LOG4CXX_ASYNC_APPENDER_H

