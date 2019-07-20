/*
 * ISocketEventHandler.hpp
 *
 *  Created on: 05/01/2019
 *      Author: jamil
 */

#ifndef SOCKET_ISOCKETEVENTHANDLER_HPP_
#define SOCKET_ISOCKETEVENTHANDLER_HPP_

#include <string>
#include <functional>

class ISocketEventHandler
{
public:
	using OnConnect = std::function<void()>;
	using OnReconnect = std::function<void()>;
	using OnDisconnect = std::function<void()>;
	using OnError = std::function<void ()>;
	using OnRead = std::function<void (std::string)>;
	using OnWrite = std::function<void (std::string)>;


	OnConnect on_connect;
	OnReconnect on_reconnect;
	OnDisconnect on_disconnect;
	OnError on_error;
	OnRead on_read;
	OnWrite on_write;
};


#endif /* SOCKET_ISOCKETEVENTHANDLER_HPP_ */
