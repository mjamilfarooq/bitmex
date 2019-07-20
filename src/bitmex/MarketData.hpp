/*
 * BitmexMarketData.hpp
 *
 *  Created on: 05/01/2019
 *      Author: jamil
 */

#ifndef BITMEX_MARKETDATA_HPP_
#define BITMEX_MARKETDATA_HPP_

#include "../socket/ISocketConnection.hpp"
#include "reponse/Factory.hpp"
#include "request/Command.hpp"


namespace Bitmex
{
	class MarketData
	{
	public:
		MarketData(ISocketConnection& connection):connection(connection)
		{
			handlers.on_connect = [](){
				std::cout<<"Connection Established!!"<<std::endl;
			};

			handlers.on_reconnect = handlers.on_error = handlers.on_disconnect = [](){};

			handlers.on_write = [](std::string buffer){};
			handlers.on_read = [this](std::string buffer){
	//			std::cout<<"data: "<<buffer<<std::endl;
				this->response(buffer);
			};

			connection.connect(handlers);
			connection.read();
		}

		void request(Request::Command command)
		{
			connection.write(command.to_json());
		}

		void response(std::string buffer)
		{
			auto response = Response::Factory::convert(buffer);

			auto is_table = dynamic_cast<Response::Instrument*>(response);
			if (nullptr!=is_table)
			{
				for(auto itr = is_table->data_begin(); itr!=is_table->data_end(); itr++)
				{
					std::cout<<buffer<<std::endl;
					for (auto el : itr->second)
					{
						std::cout<<el.second.get_value("")<<",";
					}
				}
			}
		}

	private:
		ISocketConnection& connection;
		ISocketEventHandler handlers;
	};

}
#endif /* BITMEX_MARKETDATA_HPP_ */
