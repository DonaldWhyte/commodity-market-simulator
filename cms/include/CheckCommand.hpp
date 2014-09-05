#ifndef CMS_CHECKCOMMAND_HPP
#define CMS_CHECKCOMMAND_HPP

#include "Command.hpp"

namespace cms
{

	/*
	 * CLASS: CheckCommand
	 * DESCRIPTION: This class executes the logic required to
	 * to execute a CHECK command.
	*/
	class CheckCommand : public Command
	{

	public:
		CheckCommand(const std::string& dealerID, OrderID orderToCheck);
		virtual ~CheckCommand();

		virtual std::string execute(OrderManagerPtr orderManager);

		OrderID orderID() const;

	private:
		OrderID orderToCheck;

	};

}

#endif