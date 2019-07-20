/*
 * Command.hpp
 *
 *  Created on: 03/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REQUEST_COMMAND_HPP_
#define BITMEX_REQUEST_COMMAND_HPP_

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <vector>
#include <string>
#include <sstream>

#include "Topic.hpp"


namespace Bitmex
{
	namespace Request
	{
		//Definitions for commands
		using OpType = std::string;
		using ArgType = std::string;
		using ArgListType = std::vector<ArgType>;



		class Command
		{
		public:
			Command(OpType op, ArgListType args = ArgListType()):op(op), args(args)
			{}

			virtual std::string to_json()
			{
				boost::property_tree::ptree pt;
				boost::property_tree::ptree pargs;

				pt.put("op", op);
				for (auto arg: this->args)
				{
					boost::property_tree::ptree a;
					a.put_value(arg);
					pargs.push_back(std::make_pair("", a));
				}
				pt.add_child("args", pargs);

				std::stringstream ss;
				boost::property_tree::write_json(ss, pt);
				return ss.str();
			}

			virtual ~Command() {}

		protected:
			OpType op;
		//protected:
			ArgListType args;
		};




		class Subscribe: public Command
		{
		public:
			Subscribe(std::vector<Topic> topics):Command("subscribe") {
				for (auto topic: topics) args.push_back(topic.to_string());
			}

			virtual ~Subscribe() {}
		};

		class Unsubscribe: public Command
		{
		public:
			Unsubscribe(std::vector<Topic> topics):Command("unsubscribe") {
				for (auto topic: topics) args.push_back(topic.to_string());
			}

			virtual ~Unsubscribe() {}
		};


		class AuthKeyExpires: public Command
		{
		public:
			AuthKeyExpires(std::string api_key, int expires, std::string signature):
				Command("authKeyExpires"),
				apiKey(api_key),
				expires(expires),
				signature(signature)
			{

			}

			virtual std::string to_json() override
			{
				boost::property_tree::ptree pt;
				boost::property_tree::ptree pargs;

				pt.put("op", op);

				{
					boost::property_tree::ptree a;
					a.put_value(apiKey);
					pargs.push_back(std::make_pair("", a));
				}

				{
					boost::property_tree::ptree a;
					a.put_value(expires);
					pargs.push_back(std::make_pair("", a));
				}

				{
					boost::property_tree::ptree a;
					a.put_value(signature);
					pargs.push_back(std::make_pair("", a));
				}

				pt.add_child("args", pargs);

				std::stringstream ss;
				boost::property_tree::write_json(ss, pt);
				return ss.str();
			}

			virtual ~AuthKeyExpires() {}

		private:
			std::string apiKey;
			int expires;
			std::string signature;

		};


	}
}


#endif /* BITMEX_REQUEST_COMMAND_HPP_ */
