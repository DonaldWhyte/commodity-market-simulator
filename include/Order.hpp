#ifndef CMS_ORDER_H
#define CMS_ORDER_H

#include <string>

namespace cms
{

	enum Commodity
	{
		COMMODITY_UNKNOWN = 0,
		COMMIDITY_GOLD,
		COMMIDITY_SILVER,
		COMMIDITY_PORK,
		COMMIDITY_OIL,
		COMMIDITY_RICE,

		// Used to iterate through enumerator, should always be last
		NUM_COMMODITIES
	};

	static const std::string COMMODITY_STRINGS[] = {
		"UNKNOWN", "GOLD", "SILV", "PORK", "OIL", "RICE"
	};	

	enum Side
	{
		SIDE_UNKNOWN = 0,
		SIDE_BUY,
		SIDE_SELL,

		NUM_SIDES
	};

	static const std::string SIDE_STRINGS[] = {
		"UNKNOWN", "BUY", "SELL" 
	};

	class Order
	{

	public:
		Order(const std::string& dealerID, Side orderSide,
			Commodity orderCommodity, int orderAmont, double orderPrice);

		const std::string& dealerID() const;
		Side side() const;
		Commodity commodity() const;
		int amount() const;
		double price() const;

		bool reduceAmount(int amountToReduce);

		/* Return textual representation of order, in the
		 * format described in the CMS' formal specification. */
		std::string toString() const;

	private:
		std::string orderDealerID;
		Side orderSide;
		Commodity orderCommodity;
		int orderAmount;
		double orderPrice;


	};

}

#endif