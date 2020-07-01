//
// Created by max on 4/24/20.
//

#ifndef LIBUSERVICE_AUTHSERVICE_H
#define LIBUSERVICE_AUTHSERVICE_H

#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <mabiphmo/uService/settings.h>
#include <boost/asio/strand.hpp>
#include <iostream>
#include "BearerToken.h"

namespace mabiphmo::uService::auth {
	class auth_exception : public std::runtime_error {
	public:
		explicit auth_exception(
				const std::string &message)
				: std::runtime_error(message) {}

		auth_exception()
				: std::runtime_error("") {}
	};

	class AuthService : public std::enable_shared_from_this<AuthService> {
		settings &settings_;
		boost::asio::io_context &ioc_;
		X509 *auth_certificate_ = nullptr;
		boost::asio::steady_timer timer_;
	public:
		AuthService(
				settings &settings,
				boost::asio::io_context &ioc)
				: settings_(settings),
				  ioc_(ioc),
				  timer_(ioc, boost::asio::chrono::minutes(15)){
			init();
		}

		~AuthService() {
			if (auth_certificate_ != nullptr) {
				X509_free(auth_certificate_);
				auth_certificate_ = nullptr;
			}
		}

		std::string encrypt(std::string &to_encrypt){
		    if(!settings_.auth_settings.service_is_auth)
		        throw auth_exception("Only Auth service can encrypt");
		    //TODO: get private key and encrypt, reload private key if cert is invalid
		    return std::string();
		}

		std::string decrypt(std::string &to_decrypt){
		    //TODO: get pubkey and decrypt, reload public key if cert is invalid
		    return std::string();
		}

	private:
		void init() {
		    //TODO: get/ generate own auth token
			edit_discovery_retry();
		}

		void edit_discovery_retry_on_timer(boost::system::error_code &ec) {
            if (ec.failed()) {
                std::cout << ec.message() << std::endl;
            }
            edit_discovery_retry();
        }

		void edit_discovery_retry() {
			if (edit_discovery()) {
				//keep-alive every 10 minutes
                std::shared_ptr<boost::asio::steady_timer> t =
                        std::make_shared<boost::asio::steady_timer>(ioc_,boost::asio::chrono::minutes(10));
                t->async_wait(boost::beast::bind_front_handler(
                        &AuthService::edit_discovery_retry_on_timer,
                        shared_from_this()));
			} else {
			    //retry every 10 seconds
				std::shared_ptr<boost::asio::steady_timer> t =
				        std::make_shared<boost::asio::steady_timer>(ioc_,boost::asio::chrono::seconds(30));
				t->async_wait(boost::beast::bind_front_handler(
						&AuthService::edit_discovery_retry_on_timer,
						shared_from_this()));
			}
		}

		bool edit_discovery() {
			//TODO
		}
	};
}

#endif //LIBUSERVICE_AUTHSERVICE_H
