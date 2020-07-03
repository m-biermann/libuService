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
		WithSsl(boost::filesystem::path &&fullChainPath, boost::filesystem::path &&privateKeyPath, unsigned int portNr = 443) = 0;

		/// Sets the hostname to match with HTTP Header (default: ignore header)
		/// \param hostname Hostname to match with HTTP Header
		/// \return this for chaining
		virtual IAppBuilder &WithHostname(std::string &&hostname) = 0;

		/// Sets the address the server listens on (default: 0.0.0.0)
		/// \param address IP address (IPv4 / IPv6)
		/// \return this for chaining
		virtual IAppBuilder &WithAddress(boost::asio::ip::address &&address) = 0;
	};
}

#endif //LIBUSERVICE_IAPPBUILDER_H