//
// Created by max on 7/6/20.
//

#ifndef USERVICE_SERVER_H
#define USERVICE_SERVER_H

#include <vector>
#include "../listener/ListenerBase.h"

namespace mabiphmo::uService::server{
	class Server{
		std::vector<std::unique_ptr<listener::ListenerBase>> listener_;
	public:
		explicit Server(std::vector<std::unique_ptr<listener::ListenerBase>> &&listener);
		void Start();
		void Stop();
	};
}

#endif //USERVICE_SERVER_H
