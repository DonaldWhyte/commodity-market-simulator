#include "Util.hpp"
#include "CMSException.hpp"
#include <sstream>

namespace cms
{

	namespace util
	{

		// NOTE: I would normally use Boost.Lexical_Cast, but since it cannot be
		// used for this assignment, I have wrote conversion functions myself,
		// which use standard library functionality.

		bool isInt(const std::string& str)
		{
			std::istringstream ss(str);
			int f;
			ss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
			// Check the entire string was consumed and if either failbit or badbit is set
			return ss.eof() && !ss.fail(); 
		}

		bool isDouble(const std::string& str)
		{
			std::istringstream ss(str);
			double f;
			ss >> std::noskipws >> f;
			return ss.eof() && !ss.fail(); 
		}

		int toInt(const std::string& str)
		{
			// Ensure given string is a valid integer
			if (!isInt(str))
			{
				throw CMSException("'" + str + "' is not a valid integer");
			}

			int converted = 0;
			std::istringstream ss(str);
			ss >> converted;
			return converted;
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
			if (!isDouble(str))
			{
				throw CMSException("'" + str + "' is not a valid double");
			}

			double converted = 0;
			std::istringstream ss(str);
			ss >> converted;
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