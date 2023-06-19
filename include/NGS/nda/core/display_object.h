#pragma once

#include "NGS/nda/defined.h"
#include "NGS/nda/container/tree.h"
#include "NGS/nda/effect/blend.h"

NDA_BEGIN

//================================================
// ��ʾ�ܹ��ɲο�AS3����ʾ�ܹ�
// ������ΪDisplayObject DisplayObjectContainer
// һ��Ϊ��ʾ����һ��Ϊ��ʾ������������ӦΪ������
// ��ʾ�����������������κ���ʾͼ����Ϣ�������AS3��ͬ����ֻ��������ʾ�����������ʾ����������
// 
// ע�⣺
// ����Ҫ�ı���ʾ����� ��ʾ���ԣ�����X��Y��Scale�ȵȣ� ʱ����Ҫ�ȵ�����ʾ�����Redraw����
// ����ı�����ʾ����Ĵ�С����ʾ������Ը������еĴ�С��������Ҫ����Resize����
// 
// Resize�������������߼���
// ������ĳ����ʾ�����Resize����ΪTRUE���������ʾ��������и���ʾ���󶼻ᱻ����ΪTRUE
// ����Ҫ�û�����Resize����ΪFALSE����Ϊ��Ӧ���ڵ���Resize()����������ΪFALSE
// ����Resize()���������ֻ�������Resize��������ΪFALSE��������Ӱ�츸��ʾ����������Resize���ԣ���Ҫע����ǣ������ʾ����Ϊ�����Ļ������ݹ������������ʾ�����Resize()����
// �������Resize�������������Resize�����Լ���������ʾ�����Resize���Զ��ᱻ����ΪFALSE
// 
// Redraw�������������߼���
// Redraw������������Resize()���������������㣬����Resize��Redraw��������ȫȫ��һ�����ԣ���Ϊ��ʾ����Ӧ����ƹ�������һ����ʾ����ֻ��Ҫ�ṩ������������ݼ���
// ����Redraw����ΪTRUEʱ������ʾ����Ϊ�������������Լ����е�����ʾ�����Redraw���Զ��ᱻ����ΪTRUE
// ����Redraw����ΪFALSEʱ��ֻ������ᱻ����ΪFALSE����ͬResize���ԣ��û��ڻ�������ĵط�������Ҫ����Redraw����ΪFALSE
// ����Redraw()�������������Ƿ�����ʾ����������ֻ���������Redraw����ΪFALSE�����ڻ��ƽ��������Redraw����
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
		NGS_LOGFL(ngs::debug, "released display object %s", name.c_str());
		NGS_Assert(!Parent(), "the display object still active");
	}

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
	constexpr static const char _tab1[] = " �� ";
	constexpr static const char _node0[] = " ����";
	constexpr static const char _node1[] = " ����";

	std::string _GetTreeStruct(std::string_view prefix)const;
protected:

private:

};



__container_ptr DisplayObject::Parent() { return down_cast<__container>(Leaf::Parent()); }
__container_ptr_cst DisplayObject::Parent()const { return down_cast<__container>(Leaf::Parent()); }

std::optional<std::reference_wrapper<__display>> DisplayObjectContainer::GetChild(nstring_view name) {
	auto it = std::ranges::find_if(_GetChildren(), [&name](__leaf_ptr leaf) -> bool {
		__display_ptr child = down_cast<__display>(leaf);
		return child->name == name;
		});
	if (it == _GetChildren().end())return {};
	return std::reference_wrapper<__display>(*down_cast<__display>(*it));
}
std::optional<std::reference_wrapper<__display_cst>> DisplayObjectContainer::GetChild(nstring_view name)const {
	auto it = std::ranges::find_if(_GetChildren(), [&name](__leaf_ptr leaf) -> bool {
		__display_ptr child = down_cast<__display>(leaf);
		return child->name == name;
		});
	if (it == _GetChildren().end())return {};
	return std::reference_wrapper<__display_cst>(*down_cast<__display_cst>(*it));
}
std::string DisplayObjectContainer::GetTreeStruct()const {
	std::string treeStruct = {};
	treeStruct += name;
	treeStruct += '\n';
	treeStruct += _GetTreeStruct("");
	return treeStruct;
}
std::string DisplayObjectContainer::_GetTreeStruct(std::string_view prefix)const {
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
