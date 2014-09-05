#ifndef CMS_POSTCOMMAND_H
#define CMS_POSTCOMMAND_H

#include "Command.hpp"
#include "Order.hpp"

namespace cms
{

	/*
	 * Class: OrderCommand
	 * Description: This class executes the logic required to
	 * to execute an ORDER command.
	*/
	class PostCommand : public Command
	{

	public:
		PostCommand(const std::string& dealerID, const Order& order);

		std::string execute(OrderManagerPtr orderManager);

		const Order& order() const;

	private:
		Order orderToPost;

	};

}

#endif