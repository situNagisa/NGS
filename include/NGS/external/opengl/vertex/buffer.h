#pragma once

#include "../basic.h"
#include "../buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct buffer_trait{};
template<class T> requires requires{ typename type_traits::object_t<T>::descriptor_type; }
struct buffer_trait<T>
{
	using descriptor_type = typename type_traits::object_t<T>::descriptor_type;
};

template<class T>
concept vertex_buffer_descriptor = mpl::mstruct::CStructureDescribe<T>;

template<class T>
concept vertex_buffer = basic::bindable<T> && vertex_buffer_descriptor<typename buffer_trait<T>::descriptor_type>;


template<mpl::mstruct::CStructureDescribe Descriptor, mpl::mstruct::CStructure VertexStorage = mpl::mstruct::struct_storage<Descriptor>>
struct buffer : buffers::buffer<enums::buffer_target::array>
{
	NGS_MPL_ENVIRON(buffer);
public:
	using descriptor_type = Descriptor;
	using vertex_storage_type = VertexStorage;

	buffer() = default;
private:
	buffers::unique_buffer<vertex_storage_type> _data{};
};



NGS_LIB_MODULE_END