#ifndef CMS_TEST_COMMANDPARSERS_H
#define CMS_TEST_COMMANDPARSERS_H

#include <gtest/gtest.h>
#include "CommandParser.hpp"
#include "ParseException.hpp"

namespace cms
{

	namespace test
	{

		class CommandParserTests : public ::testing::Test
		{

		public:
			void SetUp()
			{
				dealerManager = DealerManagerPtr(new DealerManager());
				parser = boost::shared_ptr<CommandParser>(new CommandParser(dealerManager));
			}

			void TearDown()
			{
				parser = boost::shared_ptr<CommandParser>();
				dealerManager = DealerManagerPtr();
			}

		protected:
			DealerManagerPtr dealerManager;
			boost::shared_ptr<CommandParser> parser;

		};

		TEST_F(CommandParserTests, ParseInvalidCommands)
		{
			// Empty string
			EXPECT_THROW(parser->parse(""), ParseException);
			// String which exceeds maximum length
			std::string validCommandButTooLong =
			"DB LIST " + std::string(MAX_COMMAND_LENGTH, ' ');
			EXPECT_THROW(parser->parse(validCommandButTooLong), ParseException);
			// Gibberish
			EXPECT_THROW(parser->parse("sotu58h7=h3jfhgr"), ParseException);
			// Just dealer ID
			EXPECT_THROW(parser->parse("RBS"), ParseException);
			// Dealer ID and command type (invalid dealer)
			EXPECT_THROW(parser->parse("NOTREALDEALER LIST"), ParseException);
			// Dealer ID and command type (invalid type)
			EXPECT_THROW(parser->parse("RBS HAHA"), ParseException);
			// Dealer ID and command type (valid type, not enough arguments)
			// NOTE: CHECK command should have at least one argument
			EXPECT_THROW(parser->parse("RBS CHECK"), ParseException);
			// NOTE: POST command should have at least four arguments
			EXPECT_THROW(parser->parse("RBS POST BUY GOLD"), ParseException);
		}

		TEST_F(CommandParserTests, ParseAggress)
		{
			CommandPtr command;
			boost::shared_ptr<AggressCommand> aggressCommand;

			// One aggression (with invalid order ID)
			EXPECT_THROW(parser->parse("RBS AGGRESS FOO 200"), CMSException);
			// One aggression (with invalid amount to buy/sell)
			EXPECT_THROW(parser->parse("RBS AGGRESS 1 -200"), CMSException);
			EXPECT_THROW(parser->parse("RBS AGGRESS 0 0"), CMSException);
			EXPECT_THROW(parser->parse("RBS AGGRESS 0 FOO"), CMSException);
			// One aggression (valid)
			command = parser->parse("RBS AGGRESS 1 200");
			EXPECT_EQ(command->type(), "AGGRESS");
			EXPECT_EQ(command->dealerID(), "RBS");
			aggressCommand = boost::dynamic_pointer_cast<AggressCommand>(command);
			ASSERT_FALSE(aggressCommand == boost::shared_ptr<AggressCommand>());
			ASSERT_EQ(1, aggressCommand->allOrdersToAggress().size());
			EXPECT_EQ(1, aggressCommand->allOrdersToAggress()[0].first);
			EXPECT_EQ(200, aggressCommand->allOrdersToAggress()[0].second);
			// Odd number of arguments (trailing argument)
			// The trailing argument should just be ignored!
			command = parser->parse("RBS AGGRESS 1 200 3");
			EXPECT_EQ(command->type(), "AGGRESS");
			EXPECT_EQ(command->dealerID(), "RBS");
			aggressCommand = boost::dynamic_pointer_cast<AggressCommand>(command);
			ASSERT_FALSE(aggressCommand == boost::shared_ptr<AggressCommand>());
			ASSERT_EQ(1, aggressCommand->allOrdersToAggress().size());
			EXPECT_EQ(1, aggressCommand->allOrdersToAggress()[0].first);
			EXPECT_EQ(200, aggressCommand->allOrdersToAggress()[0].second);
			// Multiple aggressions
			command = parser->parse("RBS AGGRESS 1 200 3 5000");
			EXPECT_EQ(command->type(), "AGGRESS");
			EXPECT_EQ(command->dealerID(), "RBS");
			aggressCommand = boost::dynamic_pointer_cast<AggressCommand>(command);
			ASSERT_FALSE(aggressCommand == boost::shared_ptr<AggressCommand>());
			ASSERT_EQ(2, aggressCommand->allOrdersToAggress().size());
			EXPECT_EQ(1, aggressCommand->allOrdersToAggress()[0].first);
			EXPECT_EQ(200, aggressCommand->allOrdersToAggress()[0].second);
			EXPECT_EQ(3, aggressCommand->allOrdersToAggress()[1].first);
			EXPECT_EQ(5000, aggressCommand->allOrdersToAggress()[1].second);
		}

		TEST_F(CommandParserTests, ParseCheck)
		{
			// Non-integer argument
			EXPECT_THROW(parser->parse("RBS CHECK NDFFGH"), CMSException);
			// Integer argument
			CommandPtr command = parser->parse("RBS CHECK 2");
			EXPECT_EQ("RBS", command->dealerID());
			EXPECT_EQ("CHECK", command->type());
			boost::shared_ptr<CheckCommand> checkCommand =
				boost::dynamic_pointer_cast<CheckCommand>(command);
			// Ensure downcast was successful
			ASSERT_FALSE(checkCommand == boost::shared_ptr<CheckCommand>());
			EXPECT_EQ(2, checkCommand->orderID());
		}

		TEST_F(CommandParserTests, ParseList)
		{
			CommandPtr command;
			boost::shared_ptr<ListCommand> listCommand;

			// No arguments
			command = parser->parse("RBS LIST");
			EXPECT_EQ("RBS", command->dealerID());
			EXPECT_EQ("LIST", command->type());
			listCommand = boost::dynamic_pointer_cast<ListCommand>(command);
			ASSERT_FALSE(listCommand == boost::shared_ptr<ListCommand>());
			EXPECT_EQ(COMMODITY_UNKNOWN, listCommand->commodityFilter());
			EXPECT_EQ("", listCommand->dealerIDFilter());

			// Commodity filter (unknown commodity)
			EXPECT_THROW(parser->parse("RBS LIST HAHA"), CMSException);

			// Commodity filter (valid commodity)
			command = parser->parse("RBS LIST GOLD");
			EXPECT_EQ("RBS", command->dealerID());
			EXPECT_EQ("LIST", command->type());
			listCommand = boost::dynamic_pointer_cast<ListCommand>(command);
			ASSERT_FALSE(listCommand == boost::shared_ptr<ListCommand>());
			EXPECT_EQ(COMMODITY_GOLD, listCommand->commodityFilter());
			EXPECT_EQ("", listCommand->dealerIDFilter());

			// Commodity + dealer filter (unknown dealer)
			EXPECT_THROW(parser->parse("RBS LIST GOLD HAHA"), CMSException);

			// Commodity + dealer filter (valid dealer)
			command = parser->parse("RBS LIST GOLD DB");
			EXPECT_EQ("RBS", command->dealerID());
			EXPECT_EQ("LIST", command->type());
			listCommand = boost::dynamic_pointer_cast<ListCommand>(command);
			ASSERT_FALSE(listCommand == boost::shared_ptr<ListCommand>());
			EXPECT_EQ(COMMODITY_GOLD, listCommand->commodityFilter());
			EXPECT_EQ("DB", listCommand->dealerIDFilter());
		}

		TEST_F(CommandParserTests, ParsePost)
		{
			// Invalid side
			EXPECT_THROW(parser->parse("RBS POST FOO GOLD 2000 44.4"), CMSException);
			// Invalid commodity
			EXPECT_THROW(parser->parse("RBS POST BUY FOO 2000 44.4"), CMSException);
			// Invalid amount
			EXPECT_THROW(parser->parse("RBS POST BUY GOLD -2000 44.4"), CMSException);
			EXPECT_THROW(parser->parse("RBS POST BUY GOLD 0 44.4"), CMSException);
			EXPECT_THROW(parser->parse("RBS POST BUY GOLD FOO 44.4"), CMSException);
			// Invalid price
			EXPECT_THROW(parser->parse("RBS POST BUY GOLD 2000 44.4.4"), CMSException);
			EXPECT_THROW(parser->parse("RBS POST BUY GOLD 2000 FOO"), CMSException);

			// Valid arguments
			CommandPtr command = parser->parse("RBS POST BUY GOLD 2000 44.4");
			EXPECT_EQ("RBS", command->dealerID());
			EXPECT_EQ("POST", command->type());
			boost::shared_ptr<PostCommand> postCommand = 
				boost::dynamic_pointer_cast<PostCommand>(command);
			const Order& orderToPost = postCommand->order();
			EXPECT_EQ(SIDE_BUY, orderToPost.side());
			EXPECT_EQ(COMMODITY_GOLD, orderToPost.commodity());
			EXPECT_EQ(2000, orderToPost.amount());
			EXPECT_EQ(44.4, orderToPost.price());
		}

		TEST_F(CommandParserTests, ParseRevoke)
		{
			// Non-integer argument
			EXPECT_THROW(parser->parse("RBS REVOKE NDFFGH"), CMSException);
			// Integer argument
			CommandPtr command = parser->parse("RBS REVOKE 2");
			EXPECT_EQ("RBS", command->dealerID());
			EXPECT_EQ("REVOKE", command->type());
			boost::shared_ptr<RevokeCommand> revokeCommand =
				boost::dynamic_pointer_cast<RevokeCommand>(command);
			// Ensure downcast was successful
			ASSERT_FALSE(revokeCommand == boost::shared_ptr<RevokeCommand>());
			EXPECT_EQ(2, revokeCommand->orderID());
		}		

	}

}

#endif