#ifndef CMS_PARSEEXCEPTION_H
#define CMS_PARSEEXCEPTION_H

#include "CMSException.hpp"

namespace cms
{

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