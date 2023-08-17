#pragma once

#include "NGS/base/base.h"

NGS_BEGIN

namespace tree_struct {

class NGS_API  IChild {
	friend class  IParent;
public:
	virtual ~IChild() = default;

	IParent* GetParent() { return _parent; };
	const IParent* GetParent()const { return _parent; }


protected:
	IParent* _parent = nullptr;
};

class NGS_API  IParent {
private:
	NGS_DEFINE_TYPE(__child, IChild);
	NGS_DEFINE_TYPE(__container, IParent);
public:

	void AddChild(__child_ref child) { AddChild(child, _children.size()); }
	virtual void AddChild(__child_ref child, size_t index) {
		child._parent = this;
		_children.insert(_children.begin() + index, &child);
	}
	virtual void RemoveChild(size_t index) {
		_children[index]->_parent = nullptr;
		_children.erase(_children.begin() + index);
	}
	void RemoveChild(__child_ref child) {
		auto index = GetChildIndex(child);
		NGS_ASSERT(index != -1);
		RemoveChild(index);
	}

	void RemoveChildren() {
		while (!_children.empty()) {
			RemoveChild(0);
		}
	}

	int GetChildIndex(__child_ref child)const {
		auto it = std::ranges::find(_children, &child);
		return it == _children.end() ? -1 : int(it - _children.begin());
	}
	size_t GetNumChildren()const { return _children.size(); }

	bool Contain(__child_ref child)const { return GetChildIndex(child) != -1; }

	auto begin() { return _children.begin(); }
	auto end() { return _children.end(); }
	auto begin()const { return _children.begin(); }
	auto end()const { return _children.end(); }
protected:
	std::vector<IChild*> _children{};
};

class NGS_API  Leaf : virtual public IChild {

};

class NGS_API  Tree : virtual public IChild, virtual public IParent {
public:

private:

};

}




NGS_END
