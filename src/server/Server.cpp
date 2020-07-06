//
// Created by max on 7/6/20.
//

#include "Server.h"

namespace mabiphmo::uService::server{
	Server::Server(std::vector<std::unique_ptr<listener::ListenerBase>> &&listener) {
		listener_ = std::move(listener);
	}

	void Server::Start() {
		for(std::unique_ptr<listener::ListenerBase> &listener : listener_){
			listener->Start();
		}
	}

	void Server::Stop() {
		for(std::unique_ptr<listener::ListenerBase> &listener : listener_){
			listener->Stop();
		}
	}
}
