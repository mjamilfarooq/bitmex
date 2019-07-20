/*
 * Error.hpp
 *
 *  Created on: 06/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REPONSE_ERROR_HPP_
#define BITMEX_REPONSE_ERROR_HPP_

#include "Response.hpp"

namespace Bitmex
{
	namespace Response
	{

		class Error: public IResponse
		{
		public:
			Error(ptree& pt):IResponse(pt) {}

			virtual void from_json(const ptree& pt) override final
			{
				message = pt.get_child("error").get_value("");
			}

			virtual std::string to_json() override final
			{
				std::stringstream ss;
				ptree pt;
				pt.add("error", message);
				write_json(ss, pt);

				return ss.str();
			}

		private:
			std::string message;
		};



	}
}

#endif /* BITMEX_REPONSE_ERROR_HPP_ */
