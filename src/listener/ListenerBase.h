//
// Created by max on 7/5/20.
//

#ifndef USERVICE_LISTENERBASE_H
#define USERVICE_LISTENERBASE_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/core/error.hpp>
#include <string>
#include <mutex>
#include <mabiphmo/uService/service/IIoService.h>

namespace mabiphmo::uService::listener{
	class ListenerException : public std::runtime_error {
	public:
		explicit ListenerException(
				const std::string &message)
				: std::runtime_error(message) {}

		ListenerException()
				: std::runtime_error("") {}
	};
class ListenerBase : public service::IIoService, std::enable_shared_from_this<ListenerBase>{
		boost::asio::ip::tcp::acceptor acceptor_;
		boost::asio::ip::tcp::endpoint endpoint_;
	public:
		ListenerBase(boost::asio::io_context &ioc, boost::asio::ip::tcp::endpoint &&endpoint);
		void onStart() override;
		void onStop() override;
	private:
		void doAccept();
		void onAcceptDone(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);
	protected:
		virtual void onAccept(boost::asio::ip::tcp::socket &&socket) = 0;
	};
}

#endif //USERVICE_LISTENERBASE_H
