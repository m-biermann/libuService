//
// Created by max on 7/1/20.
//

#include <mabiphmo/uService/construction/IAppBuilder.h>
#include <mabiphmo/uService/construction/IAppLayerBuilder.h>
#include "construction/AppBuilder.h"

bool Startup(int argc, char *argv[]);
void Configure(mabiphmo::uService::construction::IAppBuilder &builder);
void ConfigureLayers(mabiphmo::uService::construction::IAppLayerBuilder &builder);

int main(int argc, char *argv[]){
    if(Startup(argc, argv)){
        mabiphmo::uService::construction::AppBuilder builder;
        Configure(builder);
        ConfigureLayers(builder.GetLayerBuilder());
	    std::shared_ptr<mabiphmo::uService::server::Server> server = builder.Build();
        server->Start();
        //TODO: build and start
    }
    else{
        //TODO: log/ print and exit
    }
}