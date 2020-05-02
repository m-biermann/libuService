//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_RESOURCE_H
#define LIBUSERVICE_RESOURCE_H

#include <string>
#include <boost/beast/http.hpp>
#include "server/session.h"

namespace de::mabiphmo::uService::resources {
	enum class resource_type {
		create,            //POST
		read,            //GET
		update,            //PUT
		delete_type,    //DELETE
		execute,        //PATCH
	};

	struct resource {
		std::string path = std::string();
		std::vector<resource_type> allowed_types = std::vector<resource_type>();
		std::vector<std::string> allowed_scopes = std::vector<std::string>();

		virtual void run(boost::beast::http::request_parser<boost::beast::http::empty_body> &&request_parser) = 0;
	};
}

#endif //LIBUSERVICE_RESOURCE_H
