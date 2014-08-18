#include <iostream>
#include "BaseInputMode.hpp"
#include "SingleConnectionServer.hpp"
#include "MultithreadedServer.hpp"
#include "Util.hpp"

using namespace cms;

int main(int argc, char* argv[])
{
	// Parse command line arguments
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " {base|ext1|ext2} {port number}" << std::endl;
		return 0;
	}
	std::string mode = argv[1];
	int port = 0;
	// Treat second argument as port number if extensions are used
	if (mode == "ext1" || mode == "ext2")
	{
		if (argc < 3)
		{
			std::cout << "Port number must be provided with mode " << mode << std::endl;
			return 0;
		}
		else
		{
			port = util::toInt(argv[2]);
		}
	}

	// Instantiate required InputMode class
	boost::shared_ptr<InputMode> inputMode( reinterpret_cast<InputMode*>(NULL) );
	if (mode == "base")
	{
		inputMode = boost::shared_ptr<InputMode>(new BaseInputMode());
	}
	else if (mode == "ext1")
	{
		inputMode = boost::shared_ptr<InputMode>(new SingleConnectionServer(port));
	}
	else if (mode == "ext2")
	{
		inputMode = boost::shared_ptr<InputMode>(new MultithreadedServer(port));
	}
	else
	{
		std::cout << "Unrecognized input mode given: " << mode << std::endl;
		return 3;
	}

	// Initialise program state and execute mode
	DealerManagerPtr dealerManager(new DealerManager());
	OrderManagerLockPtr orderManager(
		new Lock<OrderManagerPtr>(
			OrderManagerPtr(new OrderManager())
		)
	);
	boost::shared_ptr<CommandParser> commandParser(
		new CommandParser(dealerManager)
	);
	inputMode->run(orderManager, commandParser);

	return 0;
}