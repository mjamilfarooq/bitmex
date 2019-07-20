/*
 * Table.hpp
 *
 *  Created on: 06/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_REPONSE_TABLE_HPP_
#define BITMEX_REPONSE_TABLE_HPP_

#include "Response.hpp"
#include "Exception.hpp"

namespace Bitmex
{
	namespace Response
	{
		class Table: public IResponse
		{
		public:

			Table(ptree& pt):IResponse(pt) {}

			virtual void from_json(const ptree& pt) override
			{
				table = pt.get_child("table").get_value("");
				action = pt.get_child("action").get_value("");


				if (action=="partial")
				{

				}
				else if (action == "update")
				{

				}
				else if (action=="delete")
				{
				}
				else if (action=="insert")
				{

				}
				else
				{
					throw TableActionNotDefineException();
				}
			}

			virtual std::string to_json() override
			{
				std::stringstream ss;
				ptree pt;
				pt.add("table", table);
				pt.add("action", action);

				write_json(ss, pt);
				return ss.str();
			}

			//lazy loading keys
			const std::vector<std::string>& keys()
			{
				if (keys_.size()==0)
				{
					auto kee = root.get_child("keys");
					for (auto k: kee)
						keys_.push_back(k.second.get_value(""));
				}

				return keys_;
			}

			std::string types(std::string key)
			{
				return get_mapfield("types", key);
			}

			std::string foreignKeys(std::string key)
			{
				return get_mapfield("foreignKeys", key);
			}

			std::string attributes(std::string key)
			{
				return get_mapfield("attributes", key);
			}

			std::string filter(std::string key)
			{
				return get_mapfield("filter", key);
			}


			auto data_begin()
			{
				auto d = root.find("data");
				if (d==root.not_found()) throw TableDataNotPresentException();

				return d->second.begin();
			}

			auto data_end()
			{
				auto d = root.find("data");
				if (d==root.not_found()) throw TableDataNotPresentException();

				return d->second.end();
			}


		protected:

			std::string get_mapfield(std::string map_name, std::string key)
			{
				if (action!="partial") throw SupportedOnlyForPartialActionException("must be partial action to use this function");

				auto typ = root.find(map_name);
				if (typ==root.not_found())
				{
					throw MapNameNotInTheTableException(map_name);
				}


				auto atkey = typ->second.find(key);
				if (atkey==typ->second.not_found())
				{
					throw std::runtime_error("key " + key + " not found!!");
				}

				return atkey->second.get_value("");
			}

		private:
			std::string table;
			std::string action;
			std::vector<std::string> keys_;
		};

	}
}



#endif /* BITMEX_REPONSE_TABLE_HPP_ */
