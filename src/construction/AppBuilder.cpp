//
// Created by max on 7/1/20.
//

#include "AppBuilder.h"
#include "AppLayerBuilder.h"
#include "../listener/ClearTextListener.h"
#include <tuple>

namespace mabiphmo::uService::construction{
	AppBuilder::AppBuilder() : layerBuilder_(iocContainer_) {
		iocContainer_.RegisterSingletonClassFactory<boost::asio::io_context, std::tuple<>>(30);
	}

    IAppBuilder &AppBuilder::WithClearText(unsigned int portNr, boost::asio::ip::address &&address) {
        return WithService<listener::ClearTextListener, std::tuple<boost::asio::io_context>>(boost::asio::ip::tcp::endpoint(address, portNr));
    }

	IAppBuilder &AppBuilder::WithThreadCount(unsigned int threadCount) {
		iocContainer_.RegisterSingletonClassFactory<boost::asio::io_context, std::tuple<>>(threadCount);
        return *this;
    }

    IAppBuilder &AppBuilder::WithSsl(boost::filesystem::path &&fullChainPath, boost::filesystem::path &&privateKeyPath, unsigned int portNr, boost::asio::ip::address &&address) {
        sslEnabled_ = true;
        fullChainPath_ = fullChainPath;
        privateKeyPath_ = privateKeyPath;
        sslPort_ = portNr;
        return *this;
    }

	IAppBuilder &AppBuilder::WithHostname(std::string &&hostname) {
    	hostnameSet_ = true;
    	hostname_ = hostname;
		return *this;
	}

	IAppBuilder &AppBuilder::WithAddress(boost::asio::ip::address &&address) {
		address_ = address;
		return *this;
	}

	IAppLayerBuilder &AppBuilder::GetLayerBuilder() {
		return layerBuilder_;
	}

	std::shared_ptr<server::Server> AppBuilder::Build() {
		std::vector<std::shared_ptr<service::IIoService>> iIoServices = std::vector<std::shared_ptr<service::IIoService>>();
		for(std::function<std::shared_ptr<service::IIoService> (ioc::container &)> &factory : iIoServiceFactories_){
			iIoServices.emplace_back(factory(iocContainer_));
		}
		return std::make_shared<server::Server>(std::move(iIoServices));
	}
}
