/*
 * IMarketData.hpp
 *
 *  Created on: 03/01/2019
 *      Author: jamil
 */

#ifndef SOCKET_ISOCKETCONNECTION_HPP_
#define SOCKET_ISOCKETCONNECTION_HPP_

#include "ISocketEventHandler.hpp"

class ISocketConnection
{
public:
	virtual bool connect(ISocketEventHandler) = 0;
	virtual void reconnect() = 0;
	virtual void disconnect() = 0;

	virtual void write(std::string) = 0;
	virtual void read() = 0;

	virtual ~ISocketConnection()
	{}
};

#endif /* SOCKET_ISOCKETCONNECTION_HPP_ */
