/*
 * Success.hpp
 *
 *  Created on: 06/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REPONSE_SUCCESS_HPP_
#define BITMEX_REPONSE_SUCCESS_HPP_

#include "Response.hpp"

namespace Bitmex
{
	namespace Response
	{
		class Success: public IResponse
		{
		public:

			Success(ptree& pt):IResponse(pt), success(false), is_subscribe(false) {}

			virtual void from_json(const ptree& pt)
			{
				success = pt.get_child("success").get_value<bool>(false);

				auto topic = pt.find("subscribe");
				if (topic == pt.not_found())
				{
					topic = pt.find("unsubscribe");
					if (topic == pt.not_found())
					{
						throw new std::runtime_error("expected topic not found");
					}
					else is_subscribe = false;

				}
				else is_subscribe = true;

				this->topic = topic->second.get_value("");


				//command should be processed using ptree to extract the command content
		//		request = pt.get_child("request")
			}

			virtual std::string to_json() override final
			{
				std::stringstream ss;
				ptree pt;
				pt.add("success", success);
				auto cmdType = "subscribe";
				if (!is_subscribe)
					cmdType = "unsubscribe";

				pt.add(cmdType, topic);
				write_json(ss, pt);

				return ss.str();
			}

			virtual ~Success() {}

		private:

			bool success;
			bool is_subscribe;
			std::string topic;
		};

	}
}




#endif /* BITMEX_REPONSE_SUCCESS_HPP_ */
