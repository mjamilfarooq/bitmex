/*
 * Exception.hpp
 *
 *  Created on: 06/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REPONSE_EXCEPTION_HPP_
#define BITMEX_REPONSE_EXCEPTION_HPP_


namespace Bitmex
{
	namespace Response
	{

		class DataElementNotPresentException: public std::runtime_error
		{
		public:
			DataElementNotPresentException(std::string ele):
				std::runtime_error("data element isn't present with name " + ele) {}
		};

		class TableDataNotPresentException: public std::runtime_error
		{
		public:
			TableDataNotPresentException():std::runtime_error("Table data not present exception") {}
		};

		class TableActionNotDefineException: public std::runtime_error
		{
		public:
			TableActionNotDefineException():std::runtime_error("Table action not define") {}
		};

		class SupportedOnlyForPartialActionException: public std::runtime_error
		{
		public:
			SupportedOnlyForPartialActionException(std::string message):std::runtime_error("Table not define: " + message) {}
		};

		class MapNameNotInTheTableException: public std::runtime_error
		{
		public:
			MapNameNotInTheTableException(std::string name):
				std::runtime_error("map name is not in the table " + name){
			}
		};

	}
}
#endif /* BITMEX_REPONSE_EXCEPTION_HPP_ */
