#ifndef CMS_SERVERCOMMON_H
#define CMS_SERVERCOMMON_H

#include <boost/asio.hpp>

/*
 * DESCRIPTION: Contains common definitions used across
 * multiple server-related source files.
*/
namespace cms
{

	// Typedef'd for cleaner code
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> SocketPtr;

	// Size of input/output buffers (in bytes) used for socket communication
	static const unsigned int BUFFER_SIZE = 1024;

}

#endif