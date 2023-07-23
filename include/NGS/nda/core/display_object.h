#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/container/tree.h"
#include "NGS/nda/effect/blend.h"

NDA_BEGIN

//================================================
// 显示架构可参考AS3的显示架构
// 核心类为DisplayObject DisplayObjectContainer
// 一个为显示对象，一个为显示对象容器，都应为抽象类
// 显示对象容器本身不包含任何显示图像信息（这点与AS3不同），只包含子显示对象或者子显示对象容器、
// 
// 注意：
// 当需要改变显示对象的 显示属性（例如X，Y，Scale等等） 时，需要先调用显示对象的Redraw函数
// 如果改变了显示对象的大小（显示对象相对父容器中的大小），则需要调用Resize函数
// 
// Resize函数具有以下逻辑：
// 若设置某子显示对象的Resize属性为TRUE，则该子显示对象的所有父显示对象都会被设置为TRUE
// 不需要用户设置Resize属性为FALSE，因为他应该在调用Resize()函数后被设置为FALSE
// 调用Resize()函数后仅仅只将自身的Resize属性设置为FALSE，并不会影响父显示对象容器的Resize属性，但要注意的是，如果显示对象为容器的话，则会递归调用所有子显示对象的Resize()函数
// 结果就是Resize函数过后自身的Resize属性以及所有子显示对象的Resize属性都会被设置为FALSE
// 
// Redraw函数具有以下逻辑：
// Redraw函数本身并不像Resize()函数那样包含计算，比起Resize，Redraw则算完完全全的一个属性，因为显示对象不应与绘制工作绑定在一起，显示对象只需要提供绘制所需的数据即可
// 设置Redraw属性为TRUE时，若显示对象为容器，则自身以及所有的子显示对象的Redraw属性都会被设置为TRUE
// 设置Redraw属性为FALSE时，只有自身会被设置为FALSE，如同Resize属性，用户在绘制以外的地方并不需要设置Redraw属性为FALSE
// 调用Redraw()函数不论自身是否是显示对象容器都只设置自身的Redraw属性为FALSE，请在绘制结束后调用Redraw函数
// 
// 
//===============================================

class Stage;
class DisplayObject;
class DisplayObjectContainer;

NGS_TYPE_DEFINE(Stage, stage);
NGS_TYPE_DEFINE(DisplayObject, display);
NGS_TYPE_DEFINE(DisplayObjectContainer, container);

class DisplayObject : virtual public Leaf {
public:
	NGS_TYPE_DEFINE(DisplayObject, this);
public:
	DisplayObject() = default;
	DisplayObject(nstring_view name)
		: name(name)
	{}

	DisplayObject(__this_ref_cst other) = default;
	virtual ~DisplayObject() {
		NGS_LOGFL(debug, "released display object %s", name.c_str());
		NGS_ASSERT(!Parent(), "the display object still active");
	}
	bool IsContainer()const { return false; /*down_cast<__container>(this);*/ }

	virtual __number Width()const = 0;
	virtual void Width(__number value) { ScaleX((float32)value / Width()); }
	virtual __number Height()const = 0;
	virtual void Height(__number value) { ScaleY((float32)value / Height()); }

	__number ScaleX()const { return transform.GetScale().x; }
	__number ScaleY()const { return transform.GetScale().y; }
	void ScaleX(__number value) { transform.SetScale(value, ScaleY()); }
	void ScaleY(__number value) { transform.SetScale(ScaleX(), value); }

	ngs::float32 Rotation()const { return transform.GetRotation(); }
	void Rotate(ngs::float32 angle) { transform.SetRotation(angle); }

	__container_ptr Parent();
	__container_ptr_cst Parent()const;

	operator std::string()const { return ToString(); }
	virtual std::string ToString()const { return Format("[DisplayObject,%s]", name.c_str()); }
public:
	bool visible : 1 = true;

	__number x = {};
	__number y = {};

	Transform<__number> transform = {};

	nstring name = "";

	BlendMode blend = BlendMode::normal;
protected:
};

class DisplayObjectContainer :public DisplayObject, public Tree {
public:
	NGS_TYPE_DEFINE(__container, this);
public:
	using DisplayObject::DisplayObject;
	DisplayObjectContainer() = default;
	DisplayObjectContainer(__this_ref_cst other) = default;
	virtual ~DisplayObjectContainer()override {
		while (GetNumChildren()) {
			auto& child = GetChild(0);
			RemoveChild(child);
			Delete(&child);
		}
	}

	__display_ref GetChild(size_t index) { return *down_cast<__display>(Tree::_GetChild(index)); }
	__display_ref_cst GetChild(size_t index)const { return *down_cast<__display>(Tree::_GetChild(index)); }
	std::optional<std::reference_wrapper<__display>> GetChild(nstring_view name);
	std::optional<std::reference_wrapper<__display_cst>> GetChild(nstring_view name)const;

	virtual std::string ToString()const { return Format("[DisplayObjectContainer,%s number of children %d]", name.c_str(), GetNumChildren()); }
	std::string GetTreeStruct()const;

private:
	constexpr static const char _tab0[] = "   ";
	constexpr static const char _tab1[] = " │ ";
	constexpr static const char _node0[] = " ├─";
	constexpr static const char _node1[] = " └─";

	std::string _GetTreeStruct(std::string_view prefix)const;
protected:

private:

};



inline __container_ptr DisplayObject::Parent() { return down_cast<__container>(Leaf::Parent()); }
inline __container_ptr_cst DisplayObject::Parent()const { return down_cast<__container>(Leaf::Parent()); }

inline std::optional<std::reference_wrapper<__display>> DisplayObjectContainer::GetChild(nstring_view name) {
	auto it = std::ranges::find_if(_GetChildren(), [&name](__leaf_ptr leaf) -> bool {
		__display_ptr child = down_cast<__display>(leaf);
		return child->name == name;
		});
	if (it == _GetChildren().end())return {};
	return std::reference_wrapper<__display>(*down_cast<__display>(*it));
}
inline std::optional<std::reference_wrapper<__display_cst>> DisplayObjectContainer::GetChild(nstring_view name)const {
	auto it = std::ranges::find_if(_GetChildren(), [&name](__leaf_ptr leaf) -> bool {
		__display_ptr child = down_cast<__display>(leaf);
		return child->name == name;
		});
	if (it == _GetChildren().end())return {};
	return std::reference_wrapper<__display_cst>(*down_cast<__display_cst>(*it));
}
inline std::string DisplayObjectContainer::GetTreeStruct()const {
	std::string treeStruct = {};
	treeStruct += name;
	treeStruct += '\n';
	treeStruct += _GetTreeStruct("");
	return treeStruct;
}
inline std::string DisplayObjectContainer::_GetTreeStruct(std::string_view prefix)const {
	std::string treeStruct = {};
	size_t numChildren = GetNumChildren();

	for (size_t i = 0; i < numChildren; i++)
	{
		__display_ptr_cst child = &GetChild(i);
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


NDA_END
