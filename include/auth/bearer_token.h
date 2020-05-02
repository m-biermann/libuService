//
// Created by max on 4/30/20.
//

#ifndef LIBUSERVICE_BEARER_TOKEN_H
#define LIBUSERVICE_BEARER_TOKEN_H

#include <string>
#include "auth_service.h"

namespace de::mabiphmo::uService::auth {
	class bearer_token {
		std::string string_representation_;
		std::vector<std::string> scopes_;
		std::string id_;
	public:
		bearer_token(std::string &&string_representation, auth_service &auth_service)
				: string_representation_(string_representation) {
			//TODO
		}

		bearer_token(std::vector<std::string> &&scopes, auth_service &auth_service)
				: string_representation_(),
				  scopes_(scopes) {
			//TODO
		}

		bool is_valid() {
			//TODO
		}

		[[nodiscard]] const std::vector<std::string> &get_scopes() const {
			return scopes_;
		}

		[[nodiscard]] const std::string &get_id() const {
			return id_;
		}
	};
}
#endif //LIBUSERVICE_BEARER_TOKEN_H
