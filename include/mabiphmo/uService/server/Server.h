//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_SERVER_H
#define LIBUSERVICE_SERVER_H

#include <mabiphmo/uService/settings.h>
#include <mabiphmo/uService/auth/AuthService.h>
#include "../../../../src/structural/Listener.h"

namespace mabiphmo::uService::server {
	class Server {
		settings settings_;
	public:
		explicit Server(settings &&settings) : settings_(std::move(settings)) {}

		void start() {
			assert(!settings_.resources.empty() && "No resources defined");
			assert(settings_.thread_num > 0 && "No threads?");
			assert(!settings_.service_id.empty() && "No service id defined");
			assert(!settings_.service_secret.empty() && "No service secret defined");

			assert(!settings_.hostname.empty() && "No hostname defined");

			//IO Context for all I/O
			boost::asio::io_context ioc(settings_.thread_num);

			//actually start the server
			auth_service auth(settings_, ioc);
			//TODO: ssl::context, tcp::endpoint
			Listener listen(ioc, std::move(boost::asio::ssl::context()), boost::asio::ip::tcp::endpoint(), settings_);

			//run I/O on threads
			std::vector<std::thread> v;
			v.reserve(settings_.thread_num - 1);
			for(uint i = settings_.thread_num - 1; i > 0; --i){
				v.emplace_back(
						[&ioc]
						{
							ioc.run();
						});
			}
			ioc.run();
		}
	};
}

#endif //LIBUSERVICE_AUTHSERVICE_H
