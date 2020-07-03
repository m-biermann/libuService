//
// Created by max on 7/1/20.
//

#include "AppBuilder.h"

namespace mabiphmo::uService::construction{
    IAppBuilder &AppBuilder::WithClearTextPort(unsigned int portNr) {
        clearTextEnabled_ = true;
        clearTextPort_ = portNr;
        return *this;
    }

    IAppBuilder &AppBuilder::WithoutClearTextPort() {
        clearTextEnabled_ = false;
        return *this;
    }

    IAppBuilder &AppBuilder::WithThreadCount(unsigned int threadCount) {
        threadCount_ = threadCount;
        return *this;
    }

    IAppBuilder &AppBuilder::WithSsl(boost::filesystem::path &&fullChainPath, boost::filesystem::path &&privateKeyPath, unsigned int portNr) {
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
}
