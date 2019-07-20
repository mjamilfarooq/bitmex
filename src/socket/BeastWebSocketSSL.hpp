/*
 * BeastWebSocketSSL.hpp
 *
 *  Created on: 03/01/2019
 *      Author: jamil
 */

#ifndef SOCKET_BEASTWEBSOCKETSSL_HPP_
#define SOCKET_BEASTWEBSOCKETSSL_HPP_


#include <string>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;               // from <boost/asio/ssl.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>


#include "ISocketConnection.hpp"

class BeastWebSocketSSL: public ISocketConnection
{
public:
	BeastWebSocketSSL(std::string host, int port, boost::asio::io_context& io_ctx, ssl::context& ssl_ctx, std::string api_root = "/"):
		host_(host),
		port_(port),
		resolver_(io_ctx),	//global io_context for boost::asio [required for all i/o ops]
		ws_(io_ctx, ssl_ctx),
		api_root_(api_root)
	{
	}

	virtual bool connect(ISocketEventHandler events) override final
	{
		auto retval = true;
		try
		{
			events_ = events; //initialize callbacks
			auto result = resolver_.resolve(host_, std::to_string(port_));
			boost::asio::connect(
					ws_.next_layer().next_layer(),
					result.begin(),
					result.end());
			ws_.next_layer().handshake(ssl::stream_base::client);
			ws_.handshake(host_, api_root_);
			events_.on_connect();

		}
		catch(std::exception* ex)
		{
			std::cerr<<ex->what();
			retval = false;
		}

		return retval;
	}



	virtual void disconnect() override final
	{
		try
		{
			// Close the WebSocket connection
			ws_.close(websocket::close_code::normal);
			events_.on_disconnect();
		}
		catch(std::exception& ex)
		{
			std::cerr<<ex.what()<<std::endl;
		}

	}

	virtual void reconnect() override final
	{
		events_.on_reconnect();
	}

	virtual void write(std::string str) override final
	{
		// Send the message
		ws_.write(boost::asio::buffer(str.data(), str.size()));
		events_.on_write(std::string());
	}

	virtual void read() override final
	{
		ws_.async_read(b, std::bind(&BeastWebSocketSSL::on_read, this, std::placeholders::_1, std::placeholders::_2));
	}

	void on_read( boost::system::error_code ec,
	        std::size_t bytes_transferred)
	{
		if (ec)
		{
			std::cerr<<"socket failed while reading "<<ec<<std::endl;
			events_.on_error();
			return;
		}

		std::stringstream ss;
		ss<<boost::beast::buffers(b.data());

		events_.on_read(ss.str());

		b.consume(bytes_transferred);
		read();
	}

	virtual ~BeastWebSocketSSL()
	{

	}

private:

	ISocketEventHandler events_;
	const std::string host_;
	const int port_;
	tcp::resolver resolver_;
	websocket::stream<ssl::stream<tcp::socket>> ws_;
	const std::string api_root_;
	boost::beast::multi_buffer b;
};


#endif /* SOCKET_BEASTWEBSOCKETSSL_HPP_ */
