#pragma once

#include "NGS/ngl/environment/environment.h"

NGL_ENV_BEGIN

class NGS_API  EnvironmentManager : public IEnvironment {
public:
	virtual void Build()override {
		for (auto i = environments.cbegin(); i != environments.cend(); i++) {
			(*i)->Build();
		}
	}
	virtual void Destroy()override {
		for (auto i = environments.crbegin(); i != environments.crend(); i++) {
			(*i)->Destroy();
		}
	}

	template<std::derived_from<env::IEnvironment> T, class ... _Args> requires std::constructible_from<T, _Args...>
	T& AddEnvironment(_Args&&... args) {
		auto environment = std::make_shared<T>(std::forward<_Args>(args)...);
		environments.push_back(environment);
		return *environment;
	}
	template<std::derived_from<env::IEnvironment> T>
	T& AddEnvironment(std::shared_ptr<T>&& shared_ptr) {
		environments.push_back(std::move(shared_ptr));
		return *shared_ptr;
	}
public:
	std::vector<std::shared_ptr<env::IEnvironment>> environments{};
};

NGL_ENV_END
