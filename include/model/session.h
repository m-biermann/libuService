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

namespace de::mabiphmo::uService::model{
	struct session{
		boost::beast::ssl_stream<boost::beast::tcp_stream> stream;
		boost::asio::ip::tcp::endpoint endpoint;
		boost::beast::http::request_parser<boost::beast::http::empty_body> request_parser;
	};
}

#endif //LIBUSERVICE_SESSION_H
