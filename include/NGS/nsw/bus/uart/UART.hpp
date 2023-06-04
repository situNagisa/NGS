#pragma once

#include "NGS/nsw/depend.h"
#include "NGS/nsw/defined.h"


NGS_BEGIN

inline bool UART::Open(pin_t tx, pin_t rx) {

}

inline bool UART::IsOpened() const
{
	return false;
}

inline void UART::Close()
{
}

inline size_t UART::Write(ngs::byte_ptr_cst data, size_t size)
{
	return size_t();
}

inline size_t UART::Read(ngs::byte_ptr data, size_t size)
{
	return size_t();
}

NGS_END
