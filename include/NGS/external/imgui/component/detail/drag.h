#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_TVM_TV_REGISTER(imgui_scalar, ::ImGuiDataType_);

NGS_TVM_TV_INSERT(imgui_scalar, ::std::int8_t, ::ImGuiDataType_S8);
NGS_TVM_TV_INSERT(imgui_scalar, ::std::int16_t, ::ImGuiDataType_S16);
NGS_TVM_TV_INSERT(imgui_scalar, ::std::int32_t, ::ImGuiDataType_S32);
NGS_TVM_TV_INSERT(imgui_scalar, ::std::int64_t, ::ImGuiDataType_S64);

NGS_TVM_TV_INSERT(imgui_scalar, ::std::uint8_t, ::ImGuiDataType_U8);
NGS_TVM_TV_INSERT(imgui_scalar, ::std::uint16_t, ::ImGuiDataType_U16);
NGS_TVM_TV_INSERT(imgui_scalar, ::std::uint32_t, ::ImGuiDataType_U32);
NGS_TVM_TV_INSERT(imgui_scalar, ::std::uint64_t, ::ImGuiDataType_U64);

NGS_TVM_TV_INSERT(imgui_scalar, ::std::float_t, ::ImGuiDataType_Float);
NGS_TVM_TV_INSERT(imgui_scalar, ::std::double_t, ::ImGuiDataType_Double);

template<class T>
	requires ::std::same_as<::ImGuiDataType_, decltype(imgui_scalar::value<T>)>
decltype(auto) drag(
	::std::string_view label,
	T& value,
	const ::std::type_identity_t<T>& stride = 1,
	const ::std::type_identity_t<T>& min = {},
	const ::std::type_identity_t<T>& max = {},
	::std::string_view format = "",
	::ImGuiSliderFlags_ flags = {}
)
{
	return ::ImGui::DragScalar(label.data(), imgui_scalar::value<T>, &value, stride, &min, &max, format.empty() ? nullptr : format.data(), flags);
}

NGS_LIB_MODULE_END