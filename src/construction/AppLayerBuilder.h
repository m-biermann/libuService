//
// Created by max on 7/1/20.
//

#ifndef LIBUSERVICE_APPLAYERBUILDER_H
#define LIBUSERVICE_APPLAYERBUILDER_H

#include <mabiphmo/uService/construction/IAppLayerBuilder.h>
#include <mabiphmo/uService/construction/IAppBuilder.h>
#include "../layer/ILayerRunner.h"

namespace mabiphmo::uService::construction{
	class AppBuilder;
    class AppLayerBuilder : public IAppLayerBuilder{
    public:
    	explicit AppLayerBuilder(ioc::container &ioc);

    	layer::ILayerRunner Build();
    };
}

#endif //LIBUSERVICE_APPLAYERBUILDER_H
