//
// Created by max on 4/24/20.
//

#ifndef LIBUSERVICE_AUTH_SERVICE_H
#define LIBUSERVICE_AUTH_SERVICE_H

#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <de.mabiphmo/uService/settings.h>
#include <boost/asio/strand.hpp>
#include <iostream>
#include "bearer_token.h"

namespace de::mabiphmo::uService::auth {
	class auth_exception : public std::runtime_error {
	public:
		explicit auth_exception(
				const std::string &message)
				: std::runtime_error(message) {}

		auth_exception()
				: std::runtime_error("") {}
	};

	class auth_service : public std::enable_shared_from_this<auth_service> {
		settings &settings_;
		boost::asio::io_context &ioc_;
		X509 *auth_certificate_ = nullptr;
		boost::asio::steady_timer timer_;
	public:
		auth_service(
				settings &settings,
				boost::asio::io_context &ioc)
				: settings_(settings),
				  ioc_(ioc),
				  timer_(ioc, boost::asio::chrono::minutes(15)) {
			init();
		}

		~auth_service() {
			if (auth_certificate_ != nullptr) {
				X509_free(auth_certificate_);
				auth_certificate_ = nullptr;
			}
		}

		X509 *get_auth_certificate() const {
			if (auth_certificate_ == nullptr)
				throw auth_exception("Auth not connected");

			//TODO: if cert isn't valid right now, refresh it

			return auth_certificate_;
		}

	private:
		void init() {
			edit_discovery_retry();
		}

		void edit_discovery_retry_on_timer(boost::system::error_code &ec) {
			if (!ec) {
				edit_discovery_retry();
			} else {
				std::cout << ec.message() << std::endl;
			}
		}

		void edit_discovery_retry() {
			if (edit_discovery()) {
				//TODO: keep-alive
			} else {
				std::shared_ptr<boost::asio::steady_timer> t = std::make_shared<boost::asio::steady_timer>(ioc_,
																										   boost::asio::chrono::seconds(
																												   30));
				t->async_wait(boost::beast::bind_front_handler(
						&auth_service::edit_discovery_retry_on_timer,
						shared_from_this()));
			}
		}

		bool edit_discovery() {
			//TODO
		}
	};
}

#endif //LIBUSERVICE_AUTH_SERVICE_H
