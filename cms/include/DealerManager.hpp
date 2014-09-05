#ifndef CMS_DEALERMANAGER_H
#define CMS_DEALERMANAGER_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace cms
{

	/*
	 * CLASS: DealerManager
	 * DESCRIPTION: Loads all CMS dealers.
	 * For now, dealers are hard-coded. These hard-coded values
	 * were wrapped in this class. This was done to allow more
	 * complex mechanisms for loading in dealers to be added,
	 * without drastic changes to the code base.
	*/
	class DealerManager
	{

	public:
		DealerManager();

		/* Return true if the given ID represents a valid
		 * dealer that exists in the CMS. */
		bool isValidDealer(const std::string& dealerID);

	private:
		typedef std::vector<std::string> DealerCollection;
		DealerCollection dealerIDs;

	};

	typedef boost::shared_ptr<DealerManager> DealerManagerPtr;

}

#endif