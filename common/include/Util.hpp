#ifndef CMS_UTIL_H
#define CMS_UTIL_H

#include <string>

namespace cms
{

	/*
	 * Namespace: util
	 * Description: Contains generic utility functions used in multiple
	 * areas of the applications.
	*/
	namespace util
	{

		/* Converts given string to an integer. If the string does
		 * not contain a valid integer, a CMSException is thrown. */
		int toInt(const std::string& str);
		/* Converts given string to a positive integer. If the string
		 * does not contain a valid integer, or the integer is <= 0,
		 * a CMSException is thrown. */
		int toPositiveInt(const std::string& str);
		/* Converts given string to an double. If the string does
		 * not contain a valid double, a CMSException is thrown. */
		double toDouble(const std::string& str);
		/* Converts an integer value into a string. */
		std::string fromInt(int val);
		/* Converts a double value into a string. */
		std::string fromDouble(double val);

	}

}

#endif