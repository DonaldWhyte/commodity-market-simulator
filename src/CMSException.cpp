#include "CMSException.hpp"

namespace cms
{

	CMSException::CMSException(const std::string& message) : message(message)
	{
	}

	CMSException::~CMSException() throw()
	{
	}

	const char* CMSException::what() const throw()
	{
		return message.c_str();
	}

}