/*
 * Response.hpp
 *
 *  Created on: 05/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REPONSE_RESPONSE_HPP_
#define BITMEX_REPONSE_RESPONSE_HPP_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using ptree = boost::property_tree::ptree;
using namespace boost::property_tree::json_parser;

namespace Bitmex
{
	namespace Response
	{
		class IResponse
		{
		public:
			IResponse(ptree& pt):root(pt){
			}

			virtual void from_json(const ptree&) = 0;
			virtual std::string to_json() = 0;

			virtual ~IResponse() {};
		protected:
			ptree root;
		};
	}
}


#endif /* BITMEX_REPONSE_RESPONSE_HPP_ */
