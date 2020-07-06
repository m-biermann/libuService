//
// Created by max on 7/1/20.
//

#ifndef LIBUSERVICE_APPLAYERBUILDER_H
#define LIBUSERVICE_APPLAYERBUILDER_H

#include <mabiphmo/uService/construction/IAppLayerBuilder.h>
#include <mabiphmo/uService/construction/IAppBuilder.h>

namespace mabiphmo::uService::construction{
	class AppBuilder;
    class AppLayerBuilder : public IAppLayerBuilder{
    	AppBuilder &appBuilder_;
    public:
    	explicit AppLayerBuilder(AppBuilder &appBuilder);
    };
}

#endif //LIBUSERVICE_APPLAYERBUILDER_H
