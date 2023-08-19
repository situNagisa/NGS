#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/transform.h"
#include "NGS/nda/enum/blend.h"

NDA_BEGIN

class NGS_API  DisplayObject : virtual public tree_struct::IChild {
public:
	friend class  DisplayObjectContainer;

	DisplayObject() = default;
	DisplayObject(nstring_view name)
		: name(name)
	{}
	virtual ~DisplayObject() = 0 {};

	virtual std::string ToString()const { return name.empty() ? "display" : name; }

	DisplayObjectContainer* GetParent() { return std::launder(reinterpret_cast<DisplayObjectContainer*>(_parent)); }
	const DisplayObjectContainer* GetParent()const { return std::launder(reinterpret_cast<DisplayObjectContainer*>(_parent)); }

public:
	std::string name{};
	Transform transform{};
	BlendMode blend_mode = BlendMode::normal;
	mutable UserData user_data{};
};

class NGS_API  DisplayObjectContainer : public DisplayObject, virtual public tree_struct::IParent {
private:
	NGS_DEFINE_TYPE(__display, DisplayObject);
	NGS_DEFINE_TYPE(__container, DisplayObjectContainer);
public:
	using DisplayObject::DisplayObject;

	__display_ptr GetChild(size_t index) { return dynamic_cast<__display_ptr>(_children[index]); }
	__display_ptr_cst GetChild(size_t index) const { return dynamic_cast<__display_ptr_cst>(_children[index]); }

	size_t GetNumChildrenRecurse()const {
		size_t number = 0;
		for (auto& child : _children) {
			number++;
			auto container = dynamic_cast<__container_ptr_cst>(child);
			if (!container)continue;
			number += container->GetNumChildrenRecurse();
		}
		return number;
	}

	virtual std::string ToString()const override { return format("%s:[%d]", name.empty() ? "display_container" : name.c_str(), GetNumChildren()); }
	std::string GetTreeStruct()const {
		std::string treeStruct = {};
		treeStruct += name;
		treeStruct += '\n';
		treeStruct += _GetTreeStruct("");
		return treeStruct;
	}
private:
	constexpr static const char _tab0[] = "   ";
	constexpr static const char _tab1[] = " │ ";
	constexpr static const char _node0[] = " ├─";
	constexpr static const char _node1[] = " └─";

	std::string _GetTreeStruct(std::string_view prefix)const {
		std::string treeStruct = {};
		size_t numChildren = GetNumChildren();

		for (size_t i = 0; i < numChildren; i++) {
			__display_ptr_cst child = GetChild(i);
			treeStruct += prefix;
			treeStruct += i == numChildren - 1 ? _node1 : _node0;
			treeStruct += child->name;
			treeStruct += '\n';
			__container_ptr_cst container = dynamic_cast<__container_ptr_cst>(child);
			if (container)
				treeStruct += container->_GetTreeStruct(std::string(prefix) + (i == numChildren - 1 ? _tab0 : _tab1));
		}

		return treeStruct;
	}
};



NDA_END
