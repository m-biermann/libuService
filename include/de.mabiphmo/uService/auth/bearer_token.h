//
// Created by max on 4/30/20.
//

#ifndef LIBUSERVICE_BEARER_TOKEN_H
#define LIBUSERVICE_BEARER_TOKEN_H

#include <string>
#include "auth_service.h"

namespace de::mabiphmo::uService::auth {
	class bearer_token {
		std::string token_;
		std::vector<std::string> scopes_;
		std::string id_;
	public:
	    /// Creates a token object from the encrypted representation
	    /// \param encrypted_token
	    /// \param auth_service
		bearer_token(std::string &&encrypted_token, auth_service &auth_service)
				: token_(encrypted_token) {
		    std::string decrypted_token = auth_service.decrypt(encrypted_token);
			//TODO: token to scopes/ id
		}

		/// Creates a token from content
		/// \param scopes Scopes the token contains
		/// \param id User id
		/// \param auth_service
		bearer_token(std::vector<std::string> &&scopes, std::string &id, auth_service &auth_service)
				: scopes_(scopes),
				  id_(id){
            //TODO: scopes/ id to token
		    std::string decrypted_token = "";
            token_ = auth_service.encrypt(decrypted_token);
		}

		/// Checks whether the token is valid (one or more scopes, id is defined, checks timing)
		/// \return
		bool is_valid() {
			return scopes_.size() > 0 && !id_.empty();//TODO: timing
		}

		/// Checks whether the token has a scope
		/// \param scope
		/// \return
		bool has_scope(std::string &scope){
		    for(const std::string &scope_ : scopes_){
		        if(scope_ == scope)
		            return true;
		    }
		    return false;
		}

		/// Getter for User Id
		/// \return id
		[[nodiscard]] const std::string &get_id() const {
			return id_;
		}
	};
}
#endif //LIBUSERVICE_BEARER_TOKEN_H
