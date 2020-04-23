//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_SETTINGS_H
#define LIBUSERVICE_SETTINGS_H

#include <vector>
#include <model/resource.h>
#include <string>

namespace de::mabiphmo::uService{
	struct settings{
		std::vector<model::resource> resources = std::vector<model::resource>();
		uint thread_num = 10;

		boost::asio::ssl::context sslc = boost::asio::ssl::context(boost::asio::ssl::context::tlsv13_server);

		std::string hostname = std::string();
		boost::asio::ip::tcp::endpoint endpoint =
				boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("0.0.0.0"),
						443);

		std::string service_id = std::string();
		std::string service_secret = std::string();

		boost::asio::ip::tcp::endpoint oauth_service_endpoint =
				boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"),
						443);
		std::string oauth_service_hostname = std::string();
	};
}

#endif //LIBUSERVICE_SETTINGS_H
