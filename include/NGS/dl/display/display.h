#pragma once

#include "NGS/dl/defined.h"
#include "NGS/dl/display/basic.h"
#include "NGS/dl/transform.h"
#include "NGS/dl/enum/blend_mode.h"

NGS_DL_BEGIN

class DisplayObjectContainer;

class NGS_DLL_API DisplayObject : virtual public IChild<DisplayObjectContainer, IParent<DisplayObjectContainer, DisplayObject>> {
public:
	friend class DisplayObjectContainer;
	using container_type = DisplayObjectContainer;

	DisplayObject();
	explicit DisplayObject(const std::string_view name);

	virtual ~DisplayObject() override = 0;

	virtual std::string ToString()const { return name; }
public:
	std::string name = "display";
	Transform transform{};
	BlendMode blend_mode{};

	mutable UserData user_data{};
};

class NGS_DLL_API DisplayObjectContainer : public DisplayObject, virtual public IParent<DisplayObjectContainer, DisplayObject> {
public:
	using base_type = DisplayObject;
	using parent_type = IParent<DisplayObjectContainer, DisplayObject>;
	using display_type = DisplayObject;
	using container_type = DisplayObjectContainer;

public:
	using base_type::base_type;

	size_t GetNumChildrenRecurse()const;

	virtual std::string ToString()const override { return format("%s:[%d]", name.c_str(), GetNumChildren()); }
	std::string GetTreeStruct()const;
private:
};

NGS_DL_END
