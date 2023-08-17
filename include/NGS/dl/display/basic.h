#pragma once

#include "NGS/dl/defined.h"

NGS_DL_BEGIN

template<class _Parent,class _FriendParent>
class NGS_API IChild {
	using parent_type = _Parent;
	friend _FriendParent;
public:
	virtual ~IChild() = default;

	parent_type* GetParent() { return _parent; };
	const parent_type* GetParent()const { return _parent; }


protected:
	parent_type* _parent = nullptr;
};

template<class _DerivedType,class _Child>
class NGS_API IParent {
private:
	using _derived_type = _DerivedType;
public:
	using child_type = _Child;

	void AddChild(child_type* child, size_t index) {
		child->_parent = _Derived();
		_children.insert(_children.begin() + index, child);
	}
	void AddChild(child_type* child) { AddChild(child, _children.size()); }

	void RemoveChild(size_t index) {
		_children[index]->_parent = nullptr;
		_children.erase(_children.begin() + index);
	}
	void RemoveChild(child_type* child) {
		auto index = GetChildIndex(child);
		NGS_ASSERT(index != -1);
		RemoveChild(index);
	}
	void RemoveChildren() {
		while (!_children.empty()) {
			RemoveChild(size_t(0));
		}
	}

	child_type* GetChild(size_t index) { return _children[index]; }
	const child_type* GetChild(size_t index) const { return _children[index]; }

	int GetChildIndex(child_type* child)const {
		auto it = std::ranges::find(_children, child);
		return it == _children.end() ? -1 : int(it - _children.begin());
	}
	size_t GetNumChildren()const { return _children.size(); }

	bool Contain(child_type* child)const { return GetChildIndex(child) != -1; }

	auto begin() { return _children.begin(); }
	auto end() { return _children.end(); }
	auto begin()const { return _children.begin(); }
	auto end()const { return _children.end(); }
private:
	_derived_type* _Derived() { return std::launder(reinterpret_cast<_derived_type*>(this)); }
	const _derived_type* _Derived()const { return std::launder(reinterpret_cast<const _derived_type*>(this)); }
protected:
	std::vector<child_type*> _children{};
};

NGS_DL_END
