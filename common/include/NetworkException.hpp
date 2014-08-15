#ifndef CMS_NET_NETWORKEXCEPTION_H
#define CMS_NET_NETWORKEXCEPTION_H

#include "CMSException.hpp"

namespace cms
{

	namespace net
	{

		class NetworkException : public CMSException
		{

		public:
			NetworkException(const std::string& message) : CMSException(message)
			{
			}

			virtual ~NetworkException() throw()
			{
			}

		};

	}
	
}

#endif