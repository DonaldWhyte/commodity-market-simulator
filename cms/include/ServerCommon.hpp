#ifndef CMS_SERVERCOMMON_H
#define CMS_SERVERCOMMON_H

#include <boost/asio.hpp>

namespace cms
{


	typedef std::tr1::shared_ptr<boost::asio::ip::tcp::socket> SocketPtr;

	/* Size of input/output buffers (in bytes) used for socket communication. */
	static const unsigned int BUFFER_SIZE = 1024;

}

#endif