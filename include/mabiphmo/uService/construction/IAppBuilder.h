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

namespace mabiphmo::uService::construction {
	class IAppBuilder {
	public:
		/// Enables clear text, sets a port for it (default: enabled, port 80)
		/// \param portNr Port number
		/// \return this for chaining
		virtual IAppBuilder &WithClearTextPort(unsigned int portNr) = 0;

		/// Disables clear text (default: enabled)
		/// \return this for chaining
		virtual IAppBuilder &WithoutClearTextPort() = 0;

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
		WithSsl(boost::filesystem::path &&fullChainPath, boost::filesystem::path &&privateKeyPath, unsigned int portNr) = 0;

		/// Sets the hostname to match with HTTP Header (default: ignore header)
		/// \param hostname Hostname to match with HTTP Header
		/// \return this for chaining
		virtual IAppBuilder &WithHostname(std::string &&hostname) = 0;

		/// Sets the address the server listens on (default: 0.0.0.0)
		/// \param address IP address (IPv4 / IPv6)
		/// \return this for chaining
		virtual IAppBuilder &WithAddress(boost::asio::ip::address &&address) = 0;

		template <class TService, typename ...TDependencies>
		IAppBuilder &WithService(unsigned int additionalArgs, ...){
			if(additionalArgs > 0){
				va_list vList;
				va_start(vList, additionalArgs);
				ioc_.RegisterSingletonClass<TService, TDependencies...>(vList);
				va_end(vList);
			}
			else{
				ioc_.RegisterSingletonClass<TService, TDependencies...>();
			}
			return *this;
		}

		template <class TInterface, class TService, typename ...TDependencies>
		IAppBuilder &WithServiceOnInterface(unsigned int additionalArgs, ...){
			if(additionalArgs > 0){
				va_list vList;
				va_start(vList, additionalArgs);
				ioc_.RegisterSingletonClassOnInterface<TInterface, TService, TDependencies...>(vList);
				va_end(vList);
			}
			else{
				ioc_.RegisterSingletonClassOnInterface<TInterface, TService, TDependencies...>();
			}
			return *this;
		}
	protected:
		ioc::container ioc_ = ioc::container();
	};
}

#endif //LIBUSERVICE_IAPPBUILDER_H