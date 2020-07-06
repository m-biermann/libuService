//
// Created by max on 7/5/20.
//

#ifndef USERVICE_CLEARTEXTLISTENER_H
#define USERVICE_CLEARTEXTLISTENER_H

#include "ListenerBase.h"

namespace mabiphmo::uService::listener{
	class ClearTextListener : public ListenerBase{
	public:
		ClearTextListener(boost::asio::io_context &ioc, boost::asio::ip::tcp::endpoint&& endpoint);
	protected:
		void onAccept(boost::asio::ip::tcp::socket &&socket);
	};
}

#endif //USERVICE_CLEARTEXTLISTENER_H
