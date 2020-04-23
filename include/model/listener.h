//
// Created by max on 4/19/20.
//

#ifndef LIBUSERVICE_LISTENER_H
#define LIBUSERVICE_LISTENER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/error.hpp>
#include <iostream>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/asio/strand.hpp>
#include "session.h"

namespace de::mabiphmo::uService::model{
	class listener : public std::enable_shared_from_this<listener>{
		boost::asio::io_context &ioc_;
		boost::asio::ssl::context ssl_context_;
		boost::asio::ip::tcp::acceptor acceptor_;
		settings &settings_;
	public:
		listener(boost::asio::io_context &ioc,
				boost::asio::ssl::context &&ssl_context,
				const boost::asio::ip::tcp::endpoint& endpoint,
				settings &settings)
				: ioc_(ioc),
				  ssl_context_(std::move(ssl_context)),
				  acceptor_(ioc),
				  settings_(settings)
		{
			boost::beast::error_code ec;

			acceptor_.open(endpoint.protocol(), ec);
			if(ec){
				std::cerr << "open failed: " << ec.message() << std::endl;
				return;
			}

			acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
			if(ec){
				std::cerr << "address reuse failed: " << ec.message() << std::endl;
				return;
			}

			acceptor_.bind(endpoint, ec);
			if(ec){
				std::cerr << "bind failed: " << ec.message() << std::endl;
				return;
			}

			acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
			if(ec){
				std::cerr << "listen failed: " << ec.message() << std::endl;
				return;
			}
		}

		void run(){
			do_accept();
		}

	private:
		void do_accept(){
			acceptor_.async_accept(boost::asio::make_strand(ioc_),
								   boost::beast::bind_front_handler(
							&listener::on_accept,
							shared_from_this()));
		}

		void on_accept(boost::beast::error_code ec_, boost::asio::ip::tcp::socket socket_){
			if(ec_){
				std::cerr << "accept failed: " << ec_.message() << std::endl;
			}
			else{
				std::make_shared<session>(std::move(socket_), ssl_context_, settings_)->run();
			}

			do_accept();
		}
	};
}

#endif //LIBUSERVICE_LISTENER_H
