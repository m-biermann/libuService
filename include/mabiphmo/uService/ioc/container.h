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

		class ICreatorHolder{
		public:
			virtual ~ICreatorHolder()= default;
		};
		template <class T>
		class CreatorHolder : public ICreatorHolder{
			std::function<T*()> factory_;
		public:
			explicit CreatorHolder(std::function<T*()> &&factory) : factory_(factory){}
			T* operator()(){
				return factory_();
			}
		};

		std::unordered_map<std::string, std::shared_ptr<IHolder>> instanceMap_;
		std::unordered_map<std::string, std::shared_ptr<ICreatorHolder>> creatorMap_;

	public:
		template <class T,
				template<typename ...Ts> class TUnused, typename... Ts,
				typename ...TArgs>
		std::shared_ptr<T> RegisterSingletonClass(TArgs...args)
		{
			std::shared_ptr<Holder<T>> holder = std::make_shared<Holder<T>>();
			holder->instance_ = std::make_shared<T>(GetInstance<Ts>()..., args...);

			instanceMap_[typeid(T).name()] = holder;

			return holder->instance_;
		}

		template <class TInterface, class T,
				template<typename ...Ts> class TUnused, typename... Ts,
				typename ...TArgs>
		std::shared_ptr<TInterface> RegisterSingletonClassOnInterface(TArgs...args)
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");
			std::shared_ptr<Holder<TInterface>> holder = std::make_shared<Holder<TInterface>>();
			holder->instance_ = std::shared_ptr<TInterface>(new T(GetInstance<Ts>()..., args...));

			instanceMap_[typeid(TInterface).name()] = holder;

			return holder->instance_;
		}

		template <class T,
				template<typename ...Ts> class TUnused, typename... Ts,
				typename ...TArgs>
		void RegisterSingletonClassFactory(TArgs...args)
		{
			std::string typeKey = typeid(T).name();
			creatorMap_[typeKey] = std::make_shared<CreatorHolder<T>>([this, args...](){
				return new T(GetInstance<Ts>()..., args...);
			});

			std::shared_ptr<IHolder> iHolder = instanceMap_[typeKey];
			auto * holder = dynamic_cast<Holder<T>*>(iHolder.get());
			holder->instance_ = nullptr;
		}

		template <class TInterface, class T,
				template<typename ...Ts> class TUnused, typename... Ts,
				typename ...TArgs>
		void RegisterSingletonClassFactoryOnInterface(TArgs...args)
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");
			std::string typeKey = typeid(TInterface).name();
			creatorMap_[typeKey] = std::make_shared<CreatorHolder<TInterface>>([this, args...](){
				return dynamic_cast<TInterface *>(new T(GetInstance<Ts>()..., args...));
			});

			std::shared_ptr<IHolder> iHolder = instanceMap_[typeKey];
			auto * holder = dynamic_cast<Holder<TInterface>*>(iHolder.get());
			holder->instance_ = nullptr;
		}

		template <class T,
				template<typename ...Ts> class TUnused, typename... Ts,
				typename ...TArgs>
		void RegisterClassFactory(TArgs...args)
		{
			std::string typeKey = typeid(T).name();
			creatorMap_[typeKey] = std::make_shared<CreatorHolder<T>>([this, args...](){
				return new T(GetInstance<Ts>()..., args...);
			});
		}

		template <class TInterface, class T,
				template<typename ...Ts> class TUnused, typename... Ts,
				typename ...TArgs>
		void RegisterClassFactoryOnInterface(TArgs...args)
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");
			std::string typeKey = typeid(TInterface).name();
			creatorMap_[typeKey] = std::make_shared<CreatorHolder<TInterface>>([this, args...](){
				return dynamic_cast<TInterface *>(new T(GetInstance<Ts>()..., args...));
			});
		}

		template <class T>
		std::shared_ptr<T> GetInstance()
		{
			std::string typeName = typeid(T).name();
			if(typeName == typeid(container).name())
				return this;
			if(instanceMap_.find(typeName) != instanceMap_.end()){
				std::shared_ptr<IHolder> iHolder = instanceMap_[typeName];
				auto * holder = dynamic_cast<Holder<T>*>(iHolder.get());
				if(holder->instance_ == nullptr){
					std::shared_ptr<ICreatorHolder> iCreatorHolder = creatorMap_.at(typeName);
					auto * creatorHolder = dynamic_cast<CreatorHolder<T>*>(iCreatorHolder.get());
					holder->instance_ = (*creatorHolder)();
				}

				return holder->instance_;
			}
			std::shared_ptr<ICreatorHolder> iCreatorHolder = creatorMap_.at(typeName);
			auto * creatorHolder = dynamic_cast<CreatorHolder<T>*>(iCreatorHolder.get());
			return (*creatorHolder)();
		}
	};
}

#endif //USERVICE_CONTAINER_H
