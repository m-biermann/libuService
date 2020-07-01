//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_SERVER_H
#define LIBUSERVICE_SERVER_H

#include <de.mabiphmo/uService/settings.h>
#include <de.mabiphmo/uService/auth/auth_service.h>
#include "listener.h"

namespace de::mabiphmo::uService::server {
	class server {
		settings settings_;
	public:
		explicit server(settings &&settings) : settings_(std::move(settings)) {}

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
			listener listen(ioc, std::move(boost::asio::ssl::context()), boost::asio::ip::tcp::endpoint(), settings_);

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

#endif //LIBUSERVICE_AUTH_SERVICE_H
