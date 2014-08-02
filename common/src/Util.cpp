#include "Util.hpp"
#include "CMSException.hpp"
#include <sstream>

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

			int converted = 0;
			std::istringstream ss(str);
			ss >> converted;
			// Check if there was a parse error
			if (ss.rdstate() & std::ios::failbit)
			{
				throw CMSException("'" + str + "' is not a valid integer");
			}
			else
			{
				return converted;
			}			
		}

		int toPositiveInt(const std::string& str)
		{
			int converted = toInt(str);
			if (converted <= 0)
			{
				throw CMSException("'" + str + "' must be a positive integer (> 0)");
			}
			else
			{
				return converted;
			}
		}

		double toDouble(const std::string& str)
		{
			double converted = 0;
			std::istringstream ss(str);
			ss >> converted;
			// Check if there was a parse error
			if (ss.rdstate() & std::ios::failbit)
			{
				throw CMSException("'" + str + "' is not a valid double");
			}

			return converted;
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