//
// Created by max on 7/6/20.
//

#ifndef USERVICE_SERVER_H
#define USERVICE_SERVER_H

#include <vector>
#include "../listener/ListenerBase.h"

namespace mabiphmo::uService::server{
	class Server : public service::IStartableService{
		std::vector<std::shared_ptr<service::IStartableService>> startableServices_;
	public:
		explicit Server(std::vector<std::shared_ptr<service::IStartableService>> &&startableServices);
		void onStart() override;
		void onStop() override;
	};
}

#endif //USERVICE_SERVER_H
