#pragma once

#define NGS_CONCEPT_WRAPPER(wrapper_id,concept_id)				\
template<class... _Types>										\
struct wrapper_id : std::bool_constant<concept_id<_Types...>> {}\
//

#define NGS_CONCEPT_WRAPPER2(wrapper_id,...)					\
template<class... _Types>										\
struct wrapper_id : std::bool_constant<[]{return __VA_ARGS__;}()> {}\
//