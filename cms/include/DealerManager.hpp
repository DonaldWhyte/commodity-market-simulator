#ifndef CMS_DEALERMANAGER_H
#define CMS_DEALERMANAGER_H

#include <string>
#include <vector>
#include <tr1/memory>

namespace cms
{

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

	typedef std::tr1::shared_ptr<DealerManager> DealerManagerPtr;

}

#endif