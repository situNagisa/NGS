#pragma once

#include "NGS/dl/display/display.h"
#include "NGS/dl/graphic/api.h"

NGS_DL_BEGIN

NGS_HPP_INLINE DisplayObject::DisplayObject()
	: DisplayObject("display")
{}

NGS_HPP_INLINE DisplayObject::DisplayObject(const std::string_view name)
	: name(name)
{
	GraphicAPI::I().listener.display_object.constructor(this);
}

NGS_HPP_INLINE DisplayObject::~DisplayObject()
{
	GraphicAPI::I().listener.display_object.destructor(this);
}

NGS_HPP_INLINE size_t DisplayObjectContainer::GetNumChildrenRecurse() const {
	size_t number = 0;
	for (const display_type* child : _children) {
		number++;
		const auto container = as<container_type>(child);
		if (!container)continue;
		number += container->GetNumChildrenRecurse();
	}
	return number;
}

constexpr static char _tab0[] = "   ";
constexpr static char _tab1[] = " ©¦ ";
constexpr static char _node0[] = " ©À©¤";
constexpr static char _node1[] = " ©¸©¤";

NGS_HPP_GLOBAL_STATIC std::string _get_tree_struct(const DisplayObjectContainer& c,const std::string_view prefix) {
	std::string treeStruct = {};
	const size_t numChildren = c.GetNumChildren();

	for (size_t i = 0; i < numChildren; i++) {
		const DisplayObject* child = c.GetChild(i);
		treeStruct += prefix;
		treeStruct += i == numChildren - 1 ? _node1 : _node0;
		treeStruct += child->name;
		treeStruct += '\n';
		if (const DisplayObjectContainer* const container = as<DisplayObjectContainer>(child))
			treeStruct += _get_tree_struct(*container,std::string(prefix) + (i == numChildren - 1 ? _tab0 : _tab1));
	}

	return treeStruct;
}

NGS_HPP_INLINE std::string DisplayObjectContainer::GetTreeStruct() const {
	std::string treeStruct = {};
	treeStruct += name;
	treeStruct += '\n';
	treeStruct += _get_tree_struct(*this,"");
	return treeStruct;
}

NGS_DL_END