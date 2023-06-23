#pragma once

#include "NGS/nda/defined.h"

NDA_BEGIN

class Leaf;
class Tree;

class Leaf {
public:
	NGS_TYPE_DEFINE(Leaf, leaf);
	NGS_TYPE_DEFINE(Tree, tree);
public:
	virtual ~Leaf() = default;

protected:
	__tree_ptr Parent() { return _parent; }
	__tree_ptr_cst Parent()const { return _parent; }

private:
	__tree_ptr _parent = nullptr;
	friend class __tree;
};
class Tree : virtual public Leaf {
public:
	NGS_TYPE_DEFINE(Leaf, leaf);
	NGS_TYPE_DEFINE(Tree, tree);
public:

	void AddChild(__leaf_ref leaf, size_t index);
	void AddChild(__leaf_ref leaf);

	void RemoveChild(size_t index);
	void RemoveChild(__leaf_ref leaf);
	void RemoveChildren();

	int GetChildIndex(__leaf_ref_cst leaf)const;
	size_t GetNumChildren(bool recursion = false)const;

	bool Contain(__leaf_ref_cst display, bool recursion = false)const;
protected:
	__leaf_ptr _GetChild(size_t index) { return _children.at(index); }
	__leaf_ptr_cst _GetChild(size_t index)const { return _children.at(index); }
	std::vector<__leaf_ptr>& _GetChildren() { return _children; }
	const std::vector<__leaf_ptr>& _GetChildren()const { return _children; }

private:
	std::vector<__leaf_ptr> _children;
};

void Tree::AddChild(__leaf_ref leaf) {
	AddChild(leaf, _children.size());
}
void Tree::RemoveChild(__leaf_ref leaf) {
	int index = GetChildIndex(leaf);
	if (index == -1)return;
	RemoveChild(index);
}

void Tree::AddChild(__leaf_ref child, size_t index) {
	NGS_ASSERT(!child._parent, "can't add child that has parent!");
	NGS_ASSERT(index <= _children.size(), "index out of range!");
	_children.insert(_children.begin() + index, &child);
	child._parent = this;
}

int Tree::GetChildIndex(__leaf_ref_cst child) const {
	auto it = std::ranges::find(_children, &child);
	return it == _children.end() ? -1 : it - _children.begin();
}

void Tree::RemoveChild(size_t index) {
	auto& child = *_GetChild(index);
	child._parent = nullptr;
	_children.erase(_children.begin() + index);
}

void Tree::RemoveChildren() {
	for (auto child : _children) {
		child->_parent = nullptr;
	}
	_children.clear();
}

size_t Tree::GetNumChildren(bool recursion) const {
	if (!recursion)return _children.size();
	size_t num = _children.size();
	for (auto& it : _children) {
		auto tree = dynamic_cast<__tree_ptr>(it);
		if (!tree)continue;
		num += tree->GetNumChildren(true);
	}
	return num;
}

bool Tree::Contain(__leaf_ref_cst display, bool recursion) const {
	__tree_ptr_cst p = display.Parent();
	do {
		if (p == this)return true;
		p = (p->Parent());
	} while (p);
	return false;
}

NDA_END
