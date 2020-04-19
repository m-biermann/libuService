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

namespace de::mabiphmo::uService::model{
	class listener : public std::enable_shared_from_this<listener>{
		boost::asio::io_context &ioc;
		boost::asio::ssl::context &ssl_context;
		boost::asio::ip::tcp::acceptor acceptor;
	public:
		listener(boost::asio::io_context &ioc_,
				boost::asio::ssl::context &ssl_context_,
				boost::asio::ip::tcp::endpoint endpoint_)
				: ioc(ioc_),
				ssl_context(ssl_context_),
				acceptor(ioc_)
		{
			boost::beast::error_code ec;

			acceptor.open(endpoint_.protocol(), ec);
			if(ec){
				std::cerr << "open failed: " << ec.message() << std::endl;
				return;
			}

			acceptor.set_option(boost::asio::socket_base::reuse_address(true), ec);
			if(ec){
				std::cerr << "address reuse failed: " << ec.message() << std::endl;
				return;
			}

			acceptor.bind(endpoint_, ec);
			if(ec){
				std::cerr << "bind failed: " << ec.message() << std::endl;
				return;
			}

			acceptor.listen(boost::asio::socket_base::max_listen_connections, ec);
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
			acceptor.async_accept(boost::asio::make_strand(ioc),
					boost::beast::bind_front_handler(&listener::on_accept, shared_from_this()));
		}

		void on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket){
			if(ec){
				std::cerr << "accept failed: " << ec.message() << std::endl;
			}
			else{
				//TODO
			}

			do_accept();
		}
	};
}

#endif //LIBUSERVICE_LISTENER_H
