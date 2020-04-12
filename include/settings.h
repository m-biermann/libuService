//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_SETTINGS_H
#define LIBUSERVICE_SETTINGS_H

#include <vector>
#include <model/resource.h>
#include <string>

namespace de::mabiphmo::uService{
	struct settings_struct{
		std::vector<model::resource> resources = std::vector<model::resource>();
		std::string certificate_chain_file = std::string();
		std::string certificate_private_key_file = std::string();
		uint thread_num = 10;
		std::string hostname = std::string();
		std::string ip = "0.0.0.0";
		std::string port = "443";
		std::string service_id = std::string();
		std::string oauth_service_hostname = std::string();
		std::string oauth_service_port = "443";
	};

	settings_struct settings = settings_struct{};
}

#endif //LIBUSERVICE_SETTINGS_H
