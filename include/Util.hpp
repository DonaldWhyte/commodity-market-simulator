#ifndef CMS_UTIL_H
#define CMS_UTIL_H

#include <string>

namespace cms
{

	namespace util
	{

		int toInt(const std::string& str);
		std::string fromInt(int val);
		std::string fromDouble(double val);

	}

}

#endif