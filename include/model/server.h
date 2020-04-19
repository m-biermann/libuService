//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_SERVER_H
#define LIBUSERVICE_SERVER_H

#include <settings.h>
#include <thread>

namespace de::mabiphmo::uService::model{
	class server{
		settings_struct settings = settings_struct();
	public:
		server()= default;
		explicit server(settings_struct &&settings_) : settings(std::move(settings_)) {}
		void start(){
			assert(!settings.resources.empty() && "No resources defined");
			assert(settings.thread_num > 0 && "No threads?");
			assert(!settings.service_id.empty() && "No service id defined");
			assert(!settings.service_secret.empty() && "No service secret defined");

			assert(!settings.hostname.empty() && "No hostname defined");

			//IO Context for all I/O
			boost::asio::io_context ioc(settings.thread_num);

			//TODO: init auth stuff and create listener

			//run I/O on threads
			std::vector<std::thread> v;
			v.reserve(settings.thread_num - 1);
			for(uint i = settings.thread_num - 1; i > 0; --i){
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

#endif //LIBUSERVICE_SERVER_H
