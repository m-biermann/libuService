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

namespace mabiphmo::uService::ioc{
	class container{
	private:
		class IHolder
		{
		public:
			virtual ~IHolder(){}
			virtual void noop(){}
		};

		template<class T>
		class Holder : public IHolder
		{
		public:
			virtual ~Holder(){}
			std::shared_ptr<T> instance_;
		};

		std::map<std::string, std::function<void*()>> creatorMap_;
		std::map<std::string, std::shared_ptr<IHolder>> instanceMap_;

	public:

		template <class T, typename... Ts>
		void RegisterSingletonClass(va_list vList)
		{
			std::shared_ptr<Holder<T>> holder(new Holder<T>());
			holder->instance_ = std::shared_ptr<T>(new T(GetInstance<Ts>()..., vList));

			instanceMap_[typeid(T).name()] = holder;
		}

		template <class T, typename... Ts>
		void RegisterSingletonClass()
		{
			std::shared_ptr<Holder<T>> holder(new Holder<T>());
			holder->instance_ = std::shared_ptr<T>(new T(GetInstance<Ts>()...));

			instanceMap_[typeid(T).name()] = holder;
		}

		template <class TInterface, class T, typename... Ts>
		void RegisterSingletonClassOnInterface(va_list vList)
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");
			std::shared_ptr<Holder<TInterface>> holder(new Holder<TInterface>());
			holder->instance_ = std::shared_ptr<TInterface>(new T(GetInstance<Ts>()..., vList));

			instanceMap_[typeid(TInterface).name()] = holder;
		}

		template <class TInterface, class T, typename... Ts>
		void RegisterSingletonClassOnInterface()
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");
			std::shared_ptr<Holder<TInterface>> holder(new Holder<TInterface>());
			holder->instance_ = std::shared_ptr<TInterface>(new T(GetInstance<Ts>()...));

			instanceMap_[typeid(TInterface).name()] = holder;
		}

		template <class T>
		void RegisterInstance(std::shared_ptr<T> instance)
		{
			std::shared_ptr<Holder<T>> holder(new Holder<T>());
			holder->instance_ = instance;

			instanceMap_[typeid(T).name()] = holder;
		}

		template <class T, typename... Ts>
		void RegisterClass()
		{
			auto createType = [this]() -> T * {
				return new T(GetInstance<Ts>()...);
			};

			creatorMap_[typeid(T).name()] = createType;
		}

		template <class T>
		std::shared_ptr<T> GetInstance()
		{
			if(instanceMap_.find(typeid(T).name()) != instanceMap_.end())
			{
				std::shared_ptr<IHolder> iholder = instanceMap_[typeid(T).name()];

				Holder<T> * holder = dynamic_cast<Holder<T>*>(iholder.get());
				return holder->instance_;
			}
			else
			{
				return std::shared_ptr<T>(static_cast<T*>
				                          (creatorMap_[typeid(T).name()]()));
			}
		}
	};
}

#endif //USERVICE_CONTAINER_H
