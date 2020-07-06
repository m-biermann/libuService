//
// Created by max on 7/4/20.
//

#ifndef USERVICE_CONTAINER_H
#define USERVICE_CONTAINER_H

#include <cstdarg>
#include <string>
#include <type_traits>
#include <memory>
#include <map>
#include <functional>

namespace mabiphmo::uService::ioc{
	class container{
	private:
		class IHolder
		{
		public:
			virtual ~IHolder()= default;
		};

		template<class T>
		class Holder : public IHolder
		{
		public:
			~Holder() override= default;
			std::shared_ptr<T> instance_;
		};

		std::map<std::string, std::shared_ptr<IHolder>> instanceMap_;

	public:

		template <class T, typename... Ts>
		std::shared_ptr<T> RegisterSingletonClass(va_list vList)
		{
			std::shared_ptr<Holder<T>> holder(new Holder<T>());
			holder->instance_ = std::make_shared<T>(GetInstance<Ts>()..., vList);

			instanceMap_[typeid(T).name()] = holder;

			return holder->instance_;
		}

		template <class T, typename... Ts>
		std::shared_ptr<T> RegisterSingletonClass()
		{
			std::shared_ptr<Holder<T>> holder(new Holder<T>());
			holder->instance_ = std::make_shared<T>(GetInstance<Ts>()...);

			instanceMap_[typeid(T).name()] = holder;

			return holder->instance_;
		}

		template <class TInterface, class T, typename... Ts>
		std::shared_ptr<TInterface> RegisterSingletonClassOnInterface(va_list vList)
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");
			std::shared_ptr<Holder<TInterface>> holder(new Holder<TInterface>());
			holder->instance_ = std::make_shared<T>(GetInstance<Ts>()..., vList);

			instanceMap_[typeid(TInterface).name()] = holder;

			return holder->instance_;
		}

		template <class TInterface, class T, typename... Ts>
		std::shared_ptr<TInterface> RegisterSingletonClassOnInterface()
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");
			std::shared_ptr<Holder<TInterface>> holder(new Holder<TInterface>());
			holder->instance_ = std::make_shared<T>(GetInstance<Ts>()...);

			instanceMap_[typeid(TInterface).name()] = holder;

			return holder->instance_;
		}

		template <class T>
		std::shared_ptr<T> GetInstance()
		{
			if(instanceMap_.find(typeid(T).name()) != instanceMap_.end())
			{
				std::shared_ptr<IHolder> iHolder = instanceMap_[typeid(T).name()];

				auto * holder = dynamic_cast<Holder<T>*>(iHolder.get());
				return holder->instance_;
			}

			return std::shared_ptr<T>(nullptr);
		}
	};
}

#endif //USERVICE_CONTAINER_H
