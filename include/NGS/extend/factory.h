#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

template<class  _Target>
class NGS_API  Factory {

public:

	~Factory() {
		Clear();
	}
	template<class  _T, class ... _Args>
		requires std::constructible_from<_T, _Args...>&& std::is_base_of_v<_Target, _T>
	_T* Create(_Args&&... args) {
		_T* ptr;
		NGS_NEW(ptr, _T)(std::forward<_Args>(args)...);
		_targets.insert(ptr);
		return ptr;
	}
	void Destroy(_Target* ptr) {
		NGS_ASSERT(_targets.find(ptr) != _targets.end());
		NGS_DELETE(ptr);
		_targets.erase(ptr);
	}

	void Clear() {
		while (!_targets.empty()) {
			NGS_DELETE(*_targets.begin());
			_targets.erase(_targets.begin());
		}
	}

private:
	std::unordered_set<_Target*> _targets{};
};

NGS_END
