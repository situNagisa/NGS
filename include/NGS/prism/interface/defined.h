#include "../defined.h"

#define NGS_PRISM_INTERFACE_NS interfaces
#define NGS_LIB_MODULE_NAME NGS_PRISM_INTERFACE_NS
#include "NGS/lib/module.h"

#define NGS_PRISM_INTERFACE_DELEGATE(interface,description)																										\
namespace delegate																																				\
{																																								\
	template<class> struct interface {};																														\
	static_assert(NGS_NS::NGS_LIB_NAME::NGS_LIB_MODULE_NAME::interface<typename interface<NGS_NS::NGS_LIB_NAME::NGS_PRISM_DESCRIPTION_NS::description>::type>);	\
}																																								\
//
#define NGS_PRISM_INTERFACE_REGISTER(interface,description,...)																	\
template<>																														\
NGS_NS::NGS_PRISM_NS::NGS_PRISM_INTERFACE_NS::delegate::interface<NGS_NS::NGS_PRISM_NS::NGS_PRISM_DESCRIPTION_NS::description>	\
{																																\
	using type = __VA_ARGS__;																									\
}																																\
//