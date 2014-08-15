#ifndef CMS_CHECKCOMMAND_HPP
#define CMS_CHECKCOMMAND_HPP

#include "Command.hpp"

namespace cms
{

	class CheckCommand : public Command
	{

	public:
		CheckCommand(const std::string& dealerID, OrderID orderToCheck);
		virtual ~CheckCommand();

		virtual std::string execute(OrderManagerPtr orderManager);

	private:
		OrderID orderToCheck;

	};

}

#endif