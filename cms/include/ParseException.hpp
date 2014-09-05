#ifndef CMS_PARSEEXCEPTION_H
#define CMS_PARSEEXCEPTION_H

#include "CMSException.hpp"

namespace cms
{

	/*
	 * CLASS: ParseException
	 * DESCRIPTION: Exception thrown when there is an
	 * error parsing command strings.
	*/
	class ParseException : public CMSException
	{

	public:
		ParseException(const std::string& message) : CMSException(message)
		{
		}

		virtual ~ParseException() throw()
		{
		}

	};

}

#endif