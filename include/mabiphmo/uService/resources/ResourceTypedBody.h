//
// Created by max on 4/19/20.
//

#ifndef LIBUSERVICE_RESOURCETYPEDBODY_H
#define LIBUSERVICE_RESOURCETYPEDBODY_H

#include "Resource.h"

namespace mabiphmo::uService::resources {
	template<class Body>
	struct ResourceTypedBody : Resource {
		void run(session &&session_,
				 boost::beast::http::request_parser<boost::beast::http::empty_body> &&request_parser) override {
			run(session_, boost::beast::http::request_parser<Body>(request_parser));
		}

		virtual void run_typed(session &&session_, boost::beast::http::request_parser<Body> &&request_parser) = 0;
	};
}

#endif //LIBUSERVICE_RESOURCETYPEDBODY_H
