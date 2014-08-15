#include "DealerManager.hpp"

namespace cms
{

	DealerManager::DealerManager()
	{
		// For now, all of the dealers present in the CMS are hard-coded
		dealerIDs.push_back("DB");
		dealerIDs.push_back("JPM");
		dealerIDs.push_back("UBS");
		dealerIDs.push_back("RBC");
		dealerIDs.push_back("BARX");
		dealerIDs.push_back("MS");
		dealerIDs.push_back("CITI");
		dealerIDs.push_back("BOFA");
		dealerIDs.push_back("RBS");
		dealerIDs.push_back("HSBC");
	}

	bool DealerManager::isValidDealer(const std::string& dealerID)
	{
		for (DealerCollection::const_iterator id = dealerIDs.begin(); (id != dealerIDs.end()); id++)
		{
			if (dealerID == *id)
			{
				return true;
			}
		}
		return false;
	}

}