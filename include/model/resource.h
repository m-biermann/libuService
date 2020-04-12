//
// Created by max on 4/10/20.
//

#ifndef LIBUSERVICE_RESOURCE_H
#define LIBUSERVICE_RESOURCE_H

#include <string>
#include <boost/beast/http.hpp>
#include "session.h"

namespace de::mabiphmo::uService::model{
	enum class resource_type{
		create,			//POST
		read,			//GET
		update,			//PUT
		delete_type,	//DELETE
		execute,		//PATCH
	};

	struct resource{
		std::string path = std::string();
		std::vector<resource_type> types = std::vector<resource_type>();
		std::string scope = std::string();

		virtual void operator ()(session &&session_) = 0;
	};
}

#endif //LIBUSERVICE_RESOURCE_H
