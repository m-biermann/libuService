//
// Created by max on 7/6/20.
//

#ifndef USERVICE_SERVER_H
#define USERVICE_SERVER_H

#include <vector>
#include "../listener/ListenerBase.h"

namespace mabiphmo::uService::server{
	class Server{
		std::vector<service::IIoService> listener_;
	public:
		explicit Server(std::vector<std::shared_ptr<service::IIoService>> &&listener);
		void Start();
		void Stop();
	};
}

#endif //USERVICE_SERVER_H
