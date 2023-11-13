﻿#pragma once

#include "NGS/base/base.h"
#include "NGS/embedded/bus/bus_base.h"

NGS_BEGIN


class NGS_DLL_API  UART : public BusAsync<BusBase::Type::full_duplex> {
public:
	NGS_TYPE_DEFINE(BusAsync<BusBase::Type::full_duplex>, base);
public:

	bool Open(pin_t tx, pin_t rx);
	bool IsOpened()const override;
	void Close()override;

	size_t Write(ngs::byte_ptr_cst data, size_t size)override;
	using __base::Write;
	size_t Read(ngs::byte_ptr data, size_t size)override;
	using __base::Read;
private:

private:

};

NGS_END