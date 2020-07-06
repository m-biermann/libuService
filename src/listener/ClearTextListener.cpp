//
// Created by max on 7/5/20.
//

#include "ClearTextListener.h"

namespace mabiphmo::uService::listener{

	ClearTextListener::ClearTextListener(boost::asio::io_context &ioc, boost::asio::ip::tcp::endpoint &&endpoint)
			: ListenerBase(ioc, std::move(endpoint)) {
//TODO
	}

	void ClearTextListener::onAccept(boost::asio::ip::tcp::socket &&socket) {
		(void)socket;
//TODO
	}
}
