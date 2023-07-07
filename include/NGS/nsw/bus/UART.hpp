#pragma once

#include "NGS/nsw/depend.h"
#include "NGS/nsw/defined.h"


NGS_BEGIN

NGS_HPP_INLINE bool UART::Open(pin_t tx, pin_t rx) {
	return false;
}

NGS_HPP_INLINE bool UART::IsOpened() const
{
	return false;
}

NGS_HPP_INLINE void UART::Close()
{
}

NGS_HPP_INLINE size_t UART::Write(ngs::byte_ptr_cst data, size_t size)
{
	return size_t();
}

NGS_HPP_INLINE size_t UART::Read(ngs::byte_ptr data, size_t size)
{
	return size_t();
}

NGS_END
