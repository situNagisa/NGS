#pragma once

#include "NGS/base/base.h"
#include "NGS/embedded/bus/bus_base.h"

NGS_BEGIN

class NGS_DLL_API  SPI : public BusSync<BusBase::Type::full_duplex> {
public:
	NGS_TYPE_DEFINE(BusSync<BusBase::Type::full_duplex>, base);
public:

	bool Open(pin_t sck, pin_t mosi, pin_t miso, pin_t nss);
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
