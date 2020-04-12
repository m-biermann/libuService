//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_SERVER_H
#define LIBUSERVICE_SERVER_H

#include <settings.h>

namespace de::mabiphmo::uService::model{
	class server{

	public:
		void start(){
			assert(!uService::settings.resources.empty() && "No resources defined");
			assert(uService::settings.thread_num > 0 && "No threads?");
			assert(!settings.service_id.empty() && "No service id defined");
		}
	};
}

#endif //LIBUSERVICE_SERVER_H
