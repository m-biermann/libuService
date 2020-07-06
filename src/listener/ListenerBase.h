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

namespace mabiphmo::uService::listener{
	class ListenerException : public std::runtime_error {
	public:
		explicit ListenerException(
				const std::string &message)
				: std::runtime_error(message) {}

		ListenerException()
				: std::runtime_error("") {}
	};
	class ListenerBase : public std::enable_shared_from_this<ListenerBase>{
		boost::asio::ip::tcp::acceptor acceptor_;
		boost::asio::ip::tcp::endpoint endpoint_;
		boost::asio::io_context &ioc_;
		bool running_ = false;
		std::mutex runningMutex_ = std::mutex();
	public:
		ListenerBase(boost::asio::io_context &ioc, boost::asio::ip::tcp::endpoint &&endpoint);
		void Start();
		void Stop();
	private:
		void doAccept();
		void onAcceptDone(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);
	protected:
		virtual void onAccept(boost::asio::ip::tcp::socket &&socket) = 0;
	};
}

#endif //USERVICE_LISTENERBASE_H
