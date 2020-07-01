//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_SETTINGS_H
#define LIBUSERVICE_SETTINGS_H

#include <vector>
#include <string>
#include <boost/asio/ssl/context.hpp>
#include <de.mabiphmo/uService/resources/resource.h>

namespace de::mabiphmo::uService {
	struct settings {
		std::vector<resources::resource> resources = std::vector<resources::resource>();
		uint thread_num = 10;

		struct ssl_settings_{
            boost::filesystem::path full_chain = std::string();
            boost::filesystem::path private_key = std::string();
		} ssl_settings;

		std::string hostname = "localhost";
		boost::asio::address ip = boost::asio::address("0.0.0.0");
		uint port = 443;

		std::string service_id = std::string();
		std::string service_secret = std::string();

		struct auth_settings_{
            bool service_is_auth = false;

            std::string oauth_service_hostname = "localhost";
            uint oauth_service_port = 443;
		} auth_settings;

		struct file_settings_{
		    boost::filesystem::path persistence_dir = boost::filesystem::path("");//default: cwd
		    boost::filesystem::path settings_dir = boost::filesystem::path("");//default: cwd TODO: needed?
		};
	};
}

#endif //LIBUSERVICE_SETTINGS_H
