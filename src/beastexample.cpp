

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "bitmex/MarketData.hpp"
#include "bitmex/request/Command.hpp"
#include "socket/BeastWebSocketSSL.hpp"
#include "socket/root_certificates.hpp"

int main(int argc, char** argv)
{

	ssl::context ssl_ctx(ssl::context::sslv23_client);
	load_root_certificates(ssl_ctx);
	boost::asio::io_context ic;
	ISocketConnection* socket = new BeastWebSocketSSL("www.bitmex.com", 443, ic, ssl_ctx, "/realtime");


	Bitmex::MarketData marketData(*socket);

	using Subscribe = Bitmex::Request::Subscribe;
	using Instrument = Bitmex::Request::Instrument;
	using Unsubscribe = Bitmex::Request::Unsubscribe;

	marketData.request(Subscribe({Instrument("XBTUSD")}));
	std::this_thread::sleep_for(std::chrono::seconds(60));
	marketData.request(Unsubscribe({Instrument()}));
	ic.run();

    return EXIT_SUCCESS;
}
