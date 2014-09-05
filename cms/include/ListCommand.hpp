#ifndef CMS_LISTCOMMAND_HPP
#define CMS_LISTCOMMAND_HPP

#include "Command.hpp"
#include "Order.hpp"
#include "DealerManager.hpp"
#include <vector>

namespace cms
{

	/*
	 * CLASS: CheckCommand
	 * DESCRIPTION: This class executes the logic required to
	 * to execute a LIST command. Note that the commodity and
	 * dealer filter arguments in the class' constructor are
	 * OPTIONAL. If they are not given, then the filters will
	 * not be used.
	*/
	class ListCommand : public Command
	{

	public:
		ListCommand(const std::string& dealerID,
			DealerManagerPtr dealerManager,
			const std::string& commodityFilter = "",
			const std::string& dealerFilter = "");
		virtual ~ListCommand();

		virtual std::string execute(OrderManagerPtr orderManager);

		Commodity commodityFilter() const;
		const std::string& dealerIDFilter() const;

	private:
		void filterByCommodity(OrderCollection& orders, Commodity commodity);
		void filterByDealer(OrderCollection& orders, const std::string& dealerID);

		// filters
		Commodity commodityToList;
		std::string dealerToList;

	};

}

#endif