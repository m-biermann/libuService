//
// Created by max on 4/19/20.
//

#ifndef LIBUSERVICE_RESOURCE_TYPED_BODY_H
#define LIBUSERVICE_RESOURCE_TYPED_BODY_H

#include "resource.h"

namespace de::mabiphmo::uService::resources {
	template<class Body>
	struct resource_typed_body : resource {
		void run(session &&session_,
				 boost::beast::http::request_parser<boost::beast::http::empty_body> &&request_parser) override {
			run(session_, boost::beast::http::request_parser<Body>(request_parser));
		}

		virtual void run_typed(session &&session_, boost::beast::http::request_parser<Body> &&request_parser) = 0;
	};
}

#endif //LIBUSERVICE_RESOURCE_TYPED_BODY_H
