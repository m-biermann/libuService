//
// Created by max on 7/6/20.
//

#include "Server.h"

namespace mabiphmo::uService::server{
	Server::Server(std::vector<service::IIoService> &&listener) : listener_(std::move(listener)) {}

	void Server::Start() {
		for(service::IIoService &listener : listener_){
			listener.Start();
		}
	}

	void Server::Stop() {
		for(service::IIoService &listener : listener_){
			listener.Stop();
		}
	}
}
