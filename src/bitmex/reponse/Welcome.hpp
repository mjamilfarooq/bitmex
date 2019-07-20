/*
 * WelcomeResponse.hpp
 *
 *  Created on: 06/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REPONSE_WELCOME_HPP_
#define BITMEX_REPONSE_WELCOME_HPP_

#include "Response.hpp"

namespace Bitmex
{
	namespace Response
	{
		class Welcome: public IResponse
		{
		public:

			Welcome(ptree& pt):IResponse(pt) {
			}

			virtual void from_json(const ptree& pt) override final
			{
				info = pt.get_child("info").get_value("");
				version = pt.get_child("version").get_value("");
				timestamp = pt.get_child("timestamp").get_value("");
				docs = pt.get_child("docs").get_value("");
				limit = pt.get_child("limit").get_value("");
			}

			virtual std::string to_json() override final
			{
				std::stringstream ss;
				ptree pt;
				pt.add("info", info);
				pt.add("version", version);
				pt.add("timestamp", timestamp);
				pt.add("docs", docs);
				pt.add("limit", limit);

				write_json(ss, pt);

				return ss.str();
			}

			virtual ~Welcome()
			{}

		private:
			std::string info;
			std::string version;
			std::string timestamp;
			std::string docs;
			std::string limit;
		};



	}
}

#endif /* BITMEX_REPONSE_WELCOME_HPP_ */
