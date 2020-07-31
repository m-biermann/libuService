//
// Created by max on 7/6/20.
//

#ifndef USERVICE_IIOSERVICE_H
#define USERVICE_IIOSERVICE_H

#include <boost/asio/io_context.hpp>
#include "IStartableService.h"

namespace mabiphmo::uService::service{
	class IIoService : public IStartableService{
	protected:
		std::shared_ptr<boost::asio::io_context> ioContext_;
	public:
		explicit IIoService(std::shared_ptr<boost::asio::io_context> ioContext) : ioContext_(std::move(ioContext)){}
	};
}
#endif //USERVICE_IIOSERVICE_H
