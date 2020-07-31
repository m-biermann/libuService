//
// Created by max on 7/31/20.
//

#ifndef USERVICE_ISTARTABLESERVICE_H
#define USERVICE_ISTARTABLESERVICE_H

#include <mutex>

namespace mabiphmo::uService::service{
	class IStartableService{
	protected:
		bool running_ = false;
		std::mutex runningMutex_ = std::mutex();
		virtual void onStart() = 0;
		virtual void onStop() = 0;
	public:
		void Start(){
			{
				const std::lock_guard<std::mutex> lock(runningMutex_);

				if (running_)
					return;

				running_ = true;
			}

			onStart();
		}
		void Stop(){
			{
				const std::lock_guard<std::mutex> lock(runningMutex_);

				if(!running_)
					return;

				running_ = false;
			}

			onStop();
		}
	};
}

#endif //USERVICE_ISTARTABLESERVICE_H
