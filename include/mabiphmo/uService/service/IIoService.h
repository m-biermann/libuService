//
// Created by max on 7/6/20.
//

#ifndef USERVICE_IIOSERVICE_H
#define USERVICE_IIOSERVICE_H

#include <boost/asio/io_context.hpp>

namespace mabiphmo::uService::service{
	class IIoService{
		//TODO
	protected:
		boost::asio::io_context &ioContext_;
		bool running_ = false;
		std::mutex runningMutex_ = std::mutex();
		virtual void onStart() = 0;
		virtual void onStop() = 0;
	public:
		explicit IIoService(boost::asio::io_context &ioContext) : ioContext_(ioContext){}
		void Start(){
			const std::lock_guard<std::mutex> lock(runningMutex_);
			if(running_)
				return;
			running_ = true;

			onStart();
		}
		void Stop(){
			const std::lock_guard<std::mutex> lock(runningMutex_);

			running_ = false;

			onStop();
		}
	};
}
#endif //USERVICE_IIOSERVICE_H
