//
// Created by max on 7/1/20.
//

#include "AppLayerBuilder.h"
#include "AppBuilder.h"

namespace mabiphmo::uService::construction{
	AppLayerBuilder::AppLayerBuilder(ioc::container &ioc)
	: IAppLayerBuilder(ioc){}

	layer::ILayerRunner AppLayerBuilder::Build() {
		//TODO
		(void)ioc_;
		return layer::ILayerRunner();
	}
}
