#ifndef CMS_CMSEXCEPTION_H
#define CMS_CMSEXCEPTION_H

#include <exception>
#include <string>

namespace cms
{

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