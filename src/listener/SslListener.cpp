//
// Created by max on 7/5/20.
//

#include "SslListener.h"

namespace mabiphmo::uService::listener{

	SslListener::SslListener(boost::asio::io_context &ioc, boost::asio::ip::tcp::endpoint &&endpoint)
	: ListenerBase(ioc, std::move(endpoint)) {
//TODO
	}

	void SslListener::onAccept(boost::asio::ip::tcp::socket &&socket) {
		(void)socket;
//TODO
	}
}
