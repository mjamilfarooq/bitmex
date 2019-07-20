/*
 * ResponseFactory.hpp
 *
 *  Created on: 06/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REPONSE_FACTORY_HPP_
#define BITMEX_REPONSE_FACTORY_HPP_

#include <map>

#include "all.hpp"

namespace Bitmex
{
	namespace Response
	{
		class Factory
		{
		public:
			static IResponse* convert(std::string input)
			{
				//declaration of table objects mapping against their name as keys
				const std::map<std::string, std::function<IResponse* (ptree& pt)>> topics {
						std::make_pair("instrument", [](boost::property_tree::ptree& pt)
								{
									return new Instrument(pt);
								}),
				};


				std::stringstream ss(input);
				boost::property_tree::ptree pt;
				boost::property_tree::read_json(ss, pt);
				IResponse* response = nullptr;

				if (pt.find("info") != pt.not_found())
				{
					response = new Welcome(pt);
				}
				else if (pt.find("error") != pt.not_found())
				{
					response = new Error(pt);
				}
				else if (pt.find("success") != pt.not_found())
				{
					response = new Success(pt);
				}
				else if (pt.find("table") != pt.not_found())
				{
					auto table = pt.get_child("table").get_value("");
					auto is_found = topics.find(table);
					const auto not_found = topics.end();
					if (is_found != not_found)
					{
						response = is_found->second(pt);	//generating appropriate
					}
					else std::runtime_error("Topic not found " + input);
				}
				else
				{
					std::cout<<input<<std::endl;
				}

				response->from_json(pt);
				return response;
			}

		};

	}
}

#endif /* BITMEX_REPONSE_FACTORY_HPP_ */
