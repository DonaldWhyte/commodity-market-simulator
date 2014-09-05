#ifndef CMS_CMSEXCEPTION_H
#define CMS_CMSEXCEPTION_H

#include <exception>
#include <string>

namespace cms
{

	/*
	 * CLASS: CMSException
	 * DESCRIPTION: Base class for all exceptions thrown in
	 * CMS applications. Thrown when general errors occur.
	*/
	class CMSException : public std::exception
	{

	public:
		CMSException(const std::string& message);
		virtual ~CMSException() throw();
		virtual const char* what() const throw();

	private:		
		std::string message;

	};

}

#endif