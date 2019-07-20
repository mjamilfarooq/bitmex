/*
 * Instrument.hpp
 *
 *  Created on: 06/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REPONSE_INSTRUMENT_HPP_
#define BITMEX_REPONSE_INSTRUMENT_HPP_

#include "Response.hpp"

namespace Bitmex
{
	namespace Response
	{
		class Instrument: public Table
		{
		public:

			Instrument(ptree& pt):Table(pt) {}

			virtual void from_json(const ptree& pt) override
			{
				Table::from_json(pt);
			}

			virtual std::string to_json() override
			{
				return "";
			}
		};

	}
}




#endif /* BITMEX_REPONSE_INSTRUMENT_HPP_ */
