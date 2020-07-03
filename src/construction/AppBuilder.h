//
// Created by max on 7/1/20.
//

#ifndef LIBUSERVICE_APPBUILDER_H
#define LIBUSERVICE_APPBUILDER_H

#include <mabiphmo/uService/construction/IAppBuilder.h>
#include <mabiphmo/uService/construction/IAppLayerBuilder.h>
#include <string>
#include "AppLayerBuilder.h"

namespace mabiphmo::uService::construction{
    class AppBuilder : public IAppBuilder{
        IAppLayerBuilder layerBuilder_ = AppLayerBuilder();

        unsigned int threadCount_ = 30;

        boost::asio::ip::address address_ = boost::asio::ip::make_address("0.0.0.0");

        bool hostnameSet_ = false;
        std::string hostname_ = std::string();

        bool clearTextEnabled_ = true;
        unsigned int clearTextPort_ = 80;

        bool sslEnabled_ = false;
	    boost::filesystem::path fullChainPath_ = "";
	    boost::filesystem::path privateKeyPath_ = "";
        unsigned int sslPort_ = 443;
    public:
        IAppBuilder &WithClearTextPort(unsigned int portNr) override;
        IAppBuilder &WithoutClearTextPort() override;
        IAppBuilder &WithThreadCount(unsigned int threadCount) override;
        IAppBuilder &WithSsl(boost::filesystem::path &&fullChainPath, boost::filesystem::path &&privateKeyPath, unsigned int portNr) override;
	    IAppBuilder &WithHostname(std::string &&hostname) override;
	    IAppBuilder &WithAddress(boost::asio::ip::address &&address) override;
        IAppLayerBuilder &GetLayerBuilder();
    };
}

#endif //LIBUSERVICE_APPBUILDER_H
