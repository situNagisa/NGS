#pragma once

//NGS_USE_HPP

#if defined(NGS_USE_HPP)
#	define NGS_HPP_INLINE inline
#	define NGS_HPP_GLOBAL_STATIC inline
#else
#	define NGS_HPP_INLINE
#	define NGS_HPP_GLOBAL_STATIC static
#endif