/*
 * Topic.hpp
 *
 *  Created on: 03/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REQUEST_TOPIC_HPP_
#define BITMEX_REQUEST_TOPIC_HPP_

//Definitions for topics

namespace Bitmex
{
	namespace Request
	{
		using TopicNameType = std::string;

		class Topic
		{
		public:
			Topic(TopicNameType topic):name(topic)
			{}

			virtual std::string to_string() const
			{
				return name;
			}

			void add_filter(std::string filter)
			{
				name += ":" + filter;
			}

			virtual ~Topic() {}

		private:
			TopicNameType name;
		};

		#define TOPIC_DECLARATION(X,L) class X: public Topic \
		{ \
		public: \
			X(std::string filter = ""):Topic(L) { if (filter!="") add_filter(filter);} \
		};

		TOPIC_DECLARATION(Announcement, "announcement")
		TOPIC_DECLARATION(Funding, "funding")
		TOPIC_DECLARATION(Chat, "chat")
		TOPIC_DECLARATION(Connected, "connected")
		TOPIC_DECLARATION(Instrument, "instrument")
		TOPIC_DECLARATION(Insurance, "insurance")
		TOPIC_DECLARATION(Liquidation, "liquidation")
		TOPIC_DECLARATION(OrderBookL2_25, "orderBookL2_25")
		TOPIC_DECLARATION(OrderBookL2, "orderBookL2")
		TOPIC_DECLARATION(OrderBook10, "orderBookL10")
		TOPIC_DECLARATION(PublicNotifications, "publicNotifications")
		TOPIC_DECLARATION(Quote, "quotes")
		TOPIC_DECLARATION(QuoteBin1m, "quotebin1m")
		TOPIC_DECLARATION(QuoteBin5m, "quotebin5m")
		TOPIC_DECLARATION(QuoteBin1h, "quotebin1h")
		TOPIC_DECLARATION(QuoteBin1d, "quotebin1d")
		TOPIC_DECLARATION(Settlement, "settlement")
		TOPIC_DECLARATION(Trade, "trade")
		TOPIC_DECLARATION(TradeBin1m, "tradebin1m")
		TOPIC_DECLARATION(TradeBin5m, "tradebin5m")
		TOPIC_DECLARATION(TradeBin1h, "tradebin1h")
		TOPIC_DECLARATION(TradeBin1d, "tradebin1d")

		//Authenticated Topics
		TOPIC_DECLARATION(Affiliate, "affiliate")
		TOPIC_DECLARATION(Execution, "execution")
		TOPIC_DECLARATION(Order, "order")
		TOPIC_DECLARATION(Margin, "margin")
		TOPIC_DECLARATION(Position, "position")
		TOPIC_DECLARATION(PrivateNotifications, "privateNotifications")
		TOPIC_DECLARATION(Transact, "transact")
		TOPIC_DECLARATION(Wallet, "wallet")

	}
}

#endif /* BITMEX_REQUEST_TOPIC_HPP_ */
