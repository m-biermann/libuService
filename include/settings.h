//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_SETTINGS_H
#define LIBUSERVICE_SETTINGS_H

#include <vector>
#include <string>
#include <boost/asio/ssl/context.hpp>
#include <resources/resource.h>

namespace de::mabiphmo::uService {
	struct settings {
		std::vector<resources::resource> resources = std::vector<resources::resource>();
		uint thread_num = 10;

		boost::asio::ssl::context ssl_context = boost::asio::ssl::context(boost::asio::ssl::context::tlsv13_server);

		std::string hostname = std::string();
		boost::asio::ip::tcp::endpoint endpoint =
				boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("0.0.0.0"),
											   443);

		std::string service_id = std::string();
		std::string service_secret = std::string();

		bool service_is_auth = false;

		boost::asio::ip::tcp::endpoint oauth_service_endpoint =
				boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"),
											   443);
		std::string oauth_service_hostname = std::string();
	};
}

#endif //LIBUSERVICE_SETTINGS_H
