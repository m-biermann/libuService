//
// Created by max on 7/1/20.
//

#ifndef LIBUSERVICE_IAPPLAYERBUILDER_H
#define LIBUSERVICE_IAPPLAYERBUILDER_H

#include <mabiphmo/uService/ioc/container.h>

namespace mabiphmo::uService::construction{
    class IAppLayerBuilder{
    public:
	    //TODO
    protected:
	    ioc::container &ioc_;
    public:
    	explicit IAppLayerBuilder(ioc::container &ioc) : ioc_(ioc){}
    };
}

#endif //LIBUSERVICE_IAPPLAYERBUILDER_H
