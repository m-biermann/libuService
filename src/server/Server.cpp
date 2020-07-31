//
// Created by max on 7/6/20.
//

#include "Server.h"

namespace mabiphmo::uService::server{
	Server::Server(std::vector<std::shared_ptr<service::IStartableService>> &&startableServices) : startableServices_(std::move(startableServices)) {}

	void Server::onStart() {
		for(const std::shared_ptr<service::IStartableService>& startableService : startableServices_){
			startableService->Start();
		}
	}

	void Server::onStop() {
		for(const std::shared_ptr<service::IStartableService>& startableService : startableServices_){
			startableService->Stop();
		}
	}
}
