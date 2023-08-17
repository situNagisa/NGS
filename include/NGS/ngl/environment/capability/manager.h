#pragma once

#include "NGS/ngl/environment/environment.h"
#include "NGS/ngl/environment/capability/capabilities.h"
#include "NGS/ngl/environment/capability/capability.h"

NGL_ENV_BEGIN

class NGS_API  CapabilityManager : public IEnvironment{
public:
	auto& GetServer() { return _server; }
	const auto& GetServer()const { return _server; }

	void Build()override {
		_server.Build();
		for(auto& capability : _capabilities)
			capability->Build();
	}
	void Destroy()override {
		for(auto& capability : _capabilities)
			capability->Destroy();
		_server.Destroy();
	}

	template<std::derived_from<ICapability> T, class ... _Args>requires std::constructible_from<T, _Args...>
	T& AddCapability(_Args&&... args) {
		auto capability = std::make_shared<T>(std::forward<_Args>(args)...);
		_capabilities.push_back(capability);
		_server.Enable(capability->GetDependCapability());
		return *capability;
	}
	template<std::derived_from<ICapability> T>
	T& AddCapability(std::shared_ptr<T>&& capability) {
		_capabilities.push_back(std::move(capability));
		_server.Enable(capability->GetDependCapability());
		return *capability;
	}
private:
	std::vector<std::shared_ptr<ICapability>> _capabilities{};
	Capabilities _server;
};

NGL_ENV_END
