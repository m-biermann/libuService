//
// Created by max on 7/1/20.
//

#ifndef LIBUSERVICE_IAPPBUILDER_H
#define LIBUSERVICE_IAPPBUILDER_H

#include <cstdint>
#include <string>
#include "IAppLayerBuilder.h"
#include <boost/filesystem/path.hpp>
#include <boost/asio/ip/address.hpp>
#include <mabiphmo/uService/ioc/container.h>
#include <mabiphmo/uService/service/IIoService.h>

namespace mabiphmo::uService::construction {
	class IAppBuilder {
	public:
		/// Enables clear text, sets a port for it
		/// \param portNr Port number
		/// \return this for chaining
		virtual IAppBuilder &WithClearText(unsigned int portNr, boost::asio::ip::address &&address) = 0;

		/// Sets the thread count, (default: 30)
		/// \param threadCount Thread count
		/// \return this for chaining
		virtual IAppBuilder &WithThreadCount(unsigned int threadCount) = 0;

		/// Enables SSL
		/// \param fullChainPath Path to the file containing the full chain
		/// \param privateKeyPath Path to the file containing the private key
		/// \param portNr Port number
		/// \return this for chaining
		virtual IAppBuilder &
		WithSsl(boost::filesystem::path &&fullChainPath, boost::filesystem::path &&privateKeyPath, unsigned int portNr, boost::asio::ip::address &&address) = 0;

		/// Sets the hostname to match with HTTP Header (default: ignore header)
		/// \param hostname Hostname to match with HTTP Header
		/// \return this for chaining
		virtual IAppBuilder &WithHostname(std::string &&hostname) = 0;

		template <class TService,
				typename ...TDependencies,
				typename... TArgs>
		IAppBuilder &WithService(TArgs &&...args){
			if constexpr(std::is_base_of<service::IStartableService, TService>::value){
				if(iIoServiceFactories_.find(typeid(TService).name()) != iIoServiceFactories_.end()){
					iIoServiceFactories_.erase(typeid(TService).name());
				}
				iIoServiceFactories_[typeid(TService).name()] = [this]() -> std::shared_ptr<service::IStartableService> {
					return std::dynamic_pointer_cast<service::IStartableService>(iocContainer_.GetInstance<TService>());
				};
			}
			iocContainer_.RegisterSingletonClassFactory<TService, TDependencies...>(std::forward<TArgs>(args) ...);
			return *this;
		}

		template <class TInterface, class TService,
				typename ...TDependencies,
				typename... TArgs>
		IAppBuilder &WithServiceOnInterface(TArgs &&...args){
			if constexpr(std::is_base_of<service::IStartableService, TInterface>::value){
				if(iIoServiceFactories_.find(typeid(TInterface).name()) != iIoServiceFactories_.end()){
					iIoServiceFactories_.erase(typeid(TInterface).name());
				}
				iIoServiceFactories_[typeid(TInterface).name()] = [this]() -> std::shared_ptr<service::IStartableService> {
					return std::dynamic_pointer_cast<service::IStartableService>(iocContainer_.GetInstance<TInterface>());
				};
			}
			iocContainer_.RegisterSingletonClassFactoryOnInterface<TInterface, TService, TDependencies...>(std::forward<TArgs>(args)...);
			return *this;
		}
	protected:
		ioc::container iocContainer_ = ioc::container();
		std::map<std::string, std::function<std::shared_ptr<service::IStartableService> ()>> iIoServiceFactories_ = std::map<std::string, std::function<std::shared_ptr<service::IStartableService> ()>>();
	};
}

#endif //LIBUSERVICE_IAPPBUILDER_H