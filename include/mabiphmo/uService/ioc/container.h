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
class container : public std::enable_shared_from_this<container>{
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

		class ICreatorHolder {
		public:
			virtual ~ICreatorHolder()= default;
		};
		template<class T>
		class CreatorHolder : public ICreatorHolder{
			std::function<std::shared_ptr<T>()> lambda_;
		public:
			~CreatorHolder() override = default;
			explicit CreatorHolder(std::function<std::shared_ptr<T>()> &&lambda) : lambda_(std::move(lambda)){}
			std::shared_ptr<T> operator()(){
				return lambda_();
			}
		};

		std::unordered_map<std::string, std::shared_ptr<IHolder>> instanceMap_;
		std::unordered_map<std::string, std::shared_ptr<ICreatorHolder>> creatorMap_;

	public:
		template <class T,
				typename... TDependencies,
				typename ...TArgs>
		std::shared_ptr<T> RegisterSingletonClass(TArgs &&...args)
		{
			std::string typeKey = typeid(T).name();
			std::shared_ptr<Holder<T>> holder;
			if(instanceMap_.find(typeKey) != instanceMap_.end()){
				holder = std::dynamic_pointer_cast<Holder<T>>(instanceMap_[typeKey]);
			}
			else{
				holder = std::make_shared<Holder<T>>();
				instanceMap_[typeKey] = holder;
			}

			holder->instance_ = std::make_shared<T>(GetInstance<TDependencies>()..., std::forward(args)...);

			return holder->instance_;
		}

		template <class TInterface, class T,
				typename... TDependencies,
				typename ...TArgs>
		std::shared_ptr<TInterface> RegisterSingletonClassOnInterface(TArgs &&...args)
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");

			std::string typeKey = typeid(TInterface).name();
			std::shared_ptr<Holder<TInterface>> holder;
			if(instanceMap_.find(typeKey) != instanceMap_.end()){
				holder = std::dynamic_pointer_cast<Holder<TInterface>>(instanceMap_[typeKey]);
			}
			else{
				holder = std::make_shared<Holder<TInterface>>();
				instanceMap_[typeKey] = holder;
			}

			holder->instance_ = std::make_shared<T>(GetInstance<TDependencies>()..., std::forward(args)...);

			return holder->instance_;
		}

		template <class T,
				typename... TDependencies,
				typename ...TArgs>
		void RegisterSingletonClassFactory(TArgs &&...args)
		{
			std::string typeKey = typeid(T).name();
			creatorMap_[typeKey] = std::make_shared<CreatorHolder<T>>(
				[this, &args...]() -> std::shared_ptr<T>
		        {
					return std::make_shared<T>(
						GetInstance<TDependencies>()...,
				        std::forward<TArgs>(args)...);
		        });

			if(instanceMap_.find(typeKey) != instanceMap_.end()){
				auto holder = std::dynamic_pointer_cast<Holder<T>>(instanceMap_[typeKey]);
				holder->instance_.reset();
			}
			else{
				auto holder = std::make_shared<Holder<T>>();
				instanceMap_[typeKey] = holder;
			}
		}

		template <class TInterface, class T,
				typename... TDependencies,
				typename ...TArgs>
		void RegisterSingletonClassFactoryOnInterface(TArgs &&...args)
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");
			std::string typeKey = typeid(TInterface).name();
			creatorMap_[typeKey] = std::make_shared<CreatorHolder<TInterface>>(
				[this, &args...]() -> std::shared_ptr<TInterface>
		        {
					return std::make_shared<T>(
						GetInstance<TDependencies>()...,
				        std::forward<TArgs>(args)...);
		        });

			if(instanceMap_.find(typeKey) != instanceMap_.end()){
				auto holder = std::dynamic_pointer_cast<Holder<TInterface>>(instanceMap_[typeKey]);
				holder->instance_.reset();
			}
			else{
				auto holder = std::make_shared<Holder<TInterface>>();
				instanceMap_[typeKey] = holder;
			}
		}

		template <class T,
				typename... TDependencies,
				typename ...TArgs>
		void RegisterClassFactory(TArgs &&...args)
		{
			std::string typeKey = typeid(T).name();
			creatorMap_[typeKey] = std::make_shared<CreatorHolder<T>>(
				[this, &args...]() -> std::shared_ptr<T>
				{
					return std::make_shared<T>(
							GetInstance<TDependencies>()...,
							std::forward<TArgs>(args)...);
				});
		}

		template <class TInterface, class T,
				typename... TDependencies,
				typename ...TArgs>
		void RegisterClassFactoryOnInterface(TArgs &&...args)
		{
			static_assert(std::is_base_of<TInterface, T>::value, "Type has to inherit the interface it's supposed to be registered on");
			std::string typeKey = typeid(TInterface).name();
			creatorMap_[typeKey] = std::make_shared<CreatorHolder<TInterface>>(
					[this, &args...]() -> std::shared_ptr<TInterface>
					{
						return std::make_shared<T>(
								GetInstance<TDependencies>()...,
								std::forward<TArgs>(args)...);
					});
		}

		template <class T>
		std::shared_ptr<T> GetInstance()
		{
			std::string typeName = typeid(T).name();
			if constexpr(std::is_same<T, container>::value)
				return shared_from_this();
			if(instanceMap_.find(typeName) != instanceMap_.end()){
				std::shared_ptr<Holder<T>> holder =
						std::dynamic_pointer_cast<Holder<T>>(instanceMap_[typeName]);
				if(holder->instance_ == nullptr){
					std::shared_ptr<CreatorHolder<T>> creatorHolder =
							std::dynamic_pointer_cast<CreatorHolder<T>>(instanceMap_[typeName]);
					holder->instance_ = (*creatorHolder)();
				}

				return holder->instance_;
			}
			std::shared_ptr<CreatorHolder<T>> creatorHolder =
					std::dynamic_pointer_cast<CreatorHolder<T>>(instanceMap_[typeName]);
			return (*creatorHolder)();
		}
	};
}

#endif //USERVICE_CONTAINER_H
