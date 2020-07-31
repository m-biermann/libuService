//
// Created by max on 7/1/20.
//

#include "AppBuilder.h"
#include "AppLayerBuilder.h"
#include "../listener/ClearTextListener.h"
#include "../listener/SslListener.h"
#include <tuple>

namespace mabiphmo::uService::construction{
	AppBuilder::AppBuilder() : layerBuilder_(iocContainer_) {
		WithService<boost::asio::io_context>(30);
		//(void) boost::asio::io_context(30);
	}

    IAppBuilder &AppBuilder::WithClearText(unsigned int portNr, boost::asio::ip::address &&address) {
	    return WithService<listener::ClearTextListener, boost::asio::io_context>(boost::asio::ip::tcp::endpoint(address, portNr));
	    //(void) listener::ClearTextListener(iocContainer_.GetInstance<boost::asio::io_context>(), boost::asio::ip::tcp::endpoint(address, portNr));
    }

	IAppBuilder &AppBuilder::WithThreadCount(unsigned int threadCount) {
		return WithService<boost::asio::io_context>((int)threadCount);
		//(void) boost::asio::io_context((int)threadCount);
    }

    IAppBuilder &AppBuilder::WithSsl(boost::filesystem::path &&fullChainPath, boost::filesystem::path &&privateKeyPath, unsigned int portNr, boost::asio::ip::address &&address) {
	    return WithService<listener::SslListener, boost::asio::io_context>(boost::asio::ip::tcp::endpoint(address, portNr));
	    //(void)listener::SslListener(iocContainer_.GetInstance<boost::asio::io_context>(), boost::asio::ip::tcp::endpoint(address, portNr));
	    (void)fullChainPath;
	    (void)privateKeyPath;
    }

	IAppBuilder &AppBuilder::WithHostname(std::string &&hostname) {//TODO
    	hostnameSet_ = true;
    	hostname_ = hostname;
		return *this;
	}

	IAppLayerBuilder &AppBuilder::GetLayerBuilder() {
		return layerBuilder_;
	}

	std::shared_ptr<server::Server> AppBuilder::Build() {
		std::vector<std::shared_ptr<service::IStartableService>> iStartableServices = std::vector<std::shared_ptr<service::IStartableService>>();
		for(std::pair<const std::string, std::function<std::shared_ptr<service::IStartableService> ()>> &factory : iIoServiceFactories_){
			iStartableServices.emplace_back(factory.second());
		}
		return std::make_shared<server::Server>(std::move(iStartableServices));
	}
}
