//
// Created by max on 7/5/20.
//

#ifndef USERVICE_SSLLISTENER_H
#define USERVICE_SSLLISTENER_H

#include "ListenerBase.h"

namespace mabiphmo::uService::listener{
	class SslListener : public ListenerBase{
	public:
		SslListener(const std::shared_ptr<boost::asio::io_context>& ioc, boost::asio::ip::tcp::endpoint&& endpoint);
	protected:
		void onAccept(boost::asio::ip::tcp::socket &&socket);
	};
}

#endif //USERVICE_SSLLISTENER_H
