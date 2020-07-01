//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_SESSION_H
#define LIBUSERVICE_SESSION_H

#include <boost/beast/ssl/ssl_stream.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/parser.hpp>
#include <mabiphmo/uService/settings.h>

namespace mabiphmo::uService::server {
	class Session {
		boost::beast::ssl_stream<boost::beast::tcp_stream> stream_;
		settings &settings_;

	public:
		Session(boost::asio::ip::tcp::socket &&socket,
                boost::asio::ssl::context &ssl_context, settings &settings)
				: stream_(std::move(socket), ssl_context),
				  settings_(settings) {
		}
		void run(){
			//TODO
		}
	};
}

#endif //LIBUSERVICE_SESSION_H
