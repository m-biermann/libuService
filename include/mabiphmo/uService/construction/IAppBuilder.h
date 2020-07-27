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

		/// Sets the address the server listens on (default: 0.0.0.0)
		/// \param address IP address (IPv4 / IPv6)
		/// \return this for chaining
		virtual IAppBuilder &WithAddress(boost::asio::ip::address &&address) = 0;

		template <class TService,
				template<typename ...TDependencies> class T, typename ...TDependencies,
				typename... TArgs>
		IAppBuilder &WithService(TArgs...args){
			if(std::is_base_of<service::IIoService, TService>::value){
				iIoServiceFactories_.emplace_back([](ioc::container &iocContainer){
					return iocContainer.GetInstance<TService>();
				});
			}
			iocContainer_.RegisterSingletonClassFactory<TService, std::vector<TDependencies...>>(args ...);
			return *this;
		}

		template <class TInterface, class TService,
				template<typename ...TDependencies> class T, typename ...TDependencies,
				typename... TArgs>
		IAppBuilder &WithServiceOnInterface(TArgs...args){
			if(std::is_base_of<service::IIoService, TInterface>::value){
				iIoServiceFactories_.emplace_back([](ioc::container &iocContainer){
					return iocContainer.GetInstance<TInterface>();
				});
			}
			iocContainer_.RegisterSingletonClassFactoryOnInterface<TInterface, TService, std::vector<TDependencies...>>(args...);
			return *this;
		}
	protected:
		ioc::container iocContainer_ = ioc::container();
		std::vector<std::function<std::shared_ptr<service::IIoService> (ioc::container &)>> iIoServiceFactories_ = std::vector<std::function<std::shared_ptr<service::IIoService> (ioc::container &)>>();
	};
}

#endif //LIBUSERVICE_IAPPBUILDER_H