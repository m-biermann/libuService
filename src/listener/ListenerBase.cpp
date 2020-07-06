//
// Created by max on 7/5/20.
//

#include <iostream>
#include <boost/asio/strand.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include "ListenerBase.h"

namespace mabiphmo::uService::listener{
	ListenerBase::ListenerBase(boost::asio::io_context &ioc, boost::asio::ip::tcp::endpoint &&endpoint)
	: service::IIoService(ioc), acceptor_(ioc), endpoint_(endpoint) {
		boost::beast::error_code ec;

		acceptor_.open(endpoint.protocol(), ec);
		if(ec){
			std::stringstream ss;
			ss << "open failed: " << ec.message();
			throw ListenerException(ss.str());
		}

		acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
		if(ec){
			std::stringstream ss;
			ss << "address reuse failed: " << ec.message();
			throw ListenerException(ss.str());
		}

		acceptor_.bind(endpoint, ec);
		if(ec){
			std::stringstream ss;
			ss << "bind failed: " << ec.message();
			throw ListenerException(ss.str());
		}

		acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
		if(ec){
			std::stringstream ss;
			ss << "listen failed: " << ec.message();
			throw ListenerException(ss.str());
		}
	}

	void ListenerBase::doAccept() {
		acceptor_.async_accept(boost::asio::make_strand(ioContext_),
	                       boost::beast::bind_front_handler(
			                       &ListenerBase::onAcceptDone,
			                       shared_from_this()));
	}

	void ListenerBase::onAcceptDone(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) {
		if(ec){
			{
				const std::lock_guard<std::mutex> lock(runningMutex_);
				std::cerr << "accept failed: " << ec.message() << std::endl;
				if(!running_)
					return;
			}
		}
		else{
			{
				const std::lock_guard<std::mutex> lock(runningMutex_);
				if(!running_)
					return;
			}
			onAccept(std::move(socket));
		}

		doAccept();
	}

	void ListenerBase::onStart() {
		doAccept();
	}

	void ListenerBase::onStop() {}
}
