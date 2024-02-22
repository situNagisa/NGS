#pragma once

#include "../basic.h"
#include "../buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

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