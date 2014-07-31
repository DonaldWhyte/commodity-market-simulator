#include "Util.hpp"
#include <sstream>
#include <string>

namespace cms
{

	namespace util
	{

		// NOTE: I would normally use Boost.Lexical_Cast, but since it cannot be
		// used for this assignment, I have wrote a basic conversion function
		// myself, which uses standard library functionality.
		int toInt(const std::string& str)
		{
			int value = 0;
			std::istringstream stream(str);
			stream >> value;
			return value;
		}

		std::string fromInt(int val)
		{
			std::stringstream ss;
			ss << val;
			return ss.str();
		}

		std::string fromDouble(double val)
		{
			std::stringstream ss;
			ss << val;
			return ss.str();
		}

	}

}