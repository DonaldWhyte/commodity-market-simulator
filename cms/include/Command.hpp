#ifndef CMS_COMMAND_H
#define CMS_COMMAND_H

#include <boost/shared_ptr.hpp>
#include <string>
#include "OrderManager.hpp"

namespace cms
{

	/*
	 * CLASS: Command
	 * DESCRIPTION: Base class that all commands must derive from.
	 * This class stores the two fields required for every command --
	 * the command type and the dealer executing the command.
	 * Note that each subclass must implement the execute() abstract
	 * method, which contains the actual command logic.
	*/
	class Command
	{

	public:
		Command(const std::string& cmdType, const std::string& cmdDealerID);

		const std::string& type() const;
		const std::string& dealerID() const;

		/* Executes command. If exception is thrown, it is caught
		 * and its error message is contained within the returned string. */
		virtual std::string run(OrderManagerLockPtr orderManagerLock);

	private:
		/* Where command-specific logic is actually executed. 
		 * Each Command type must implement this. */
		virtual std::string execute(OrderManagerPtr orderManager) = 0;

		std::string cmdType;
		std::string cmdDealerID;

	};

	typedef boost::shared_ptr<Command> CommandPtr;

}

#endif