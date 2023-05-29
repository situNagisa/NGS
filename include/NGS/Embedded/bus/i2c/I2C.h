#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/NGS_Bit.h"
#include "NGS/Embedded/bus/Bus.h"

NGS_BEGIN

class I2C : public Bus {
protected:
	NGS_TYPE_DEFINE(ngs::uint16, address);
	NGS_TYPE_DEFINE(I2C, base);

public:
	static constexpr __address null_address = 0;
public:
	I2C();
	virtual ~I2C()override {
		_address = 0;
	}
	virtual bool Open(pin_t SDA, pin_t SCL, __address address) = 0;
	bool Open(pin_t SDA, pin_t SCL) { return Open(SDA, SCL, null_address); }

	bool IsOpened()const override;
	virtual void Close()override;

	void Enable10bitAddress(bool enable) {
		_filter = (__address)ngs::bit_max(enable ? 10 : 7);
	}
	void SetAddress(__address address) {
		_address = address & _filter;
	}
protected:
	enum class _RW {
		Write = 0,
		Read = 1,
	};

	__address _AddressWrite()const { return (_address << 1) | (int)_RW::Write; }
	__address _AddressRead()const { return (_address << 1) | (int)_RW::Read; }

protected:
	__address _filter = ngs::bit_max(7);
	__address _address = null_address;
};
template<>
constexpr Bus::Type Bus::type<I2C> = Bus::Type::half_duplex;


class I2CMaster : public I2C {
public:
	enum class ACK_Type {
		ack = 0x0,			/*!< I2C ack for each byte read */
		nack = 0x1,			/*!< I2C nack for each byte read */
		last_nack = 0x2,	/*!< I2C nack for the last byte*/
		max,
	};
public:
	bool Open(pin_t SDA, pin_t SCL, __address address)override;

	void SetACK(bool ack, ACK_Type type) { _ack = { ack,type }; }

	using __base::Write;
	size_t Write(ngs::byte_ptr_cst data, size_t size) override;
	using __base::Read;
	size_t Read(ngs::byte_ptr data, size_t size)override;

protected:
	std::pair<bool, ACK_Type> _ack = { false,ACK_Type::nack };
};

class I2CSlave : public I2C {
public:

public:
	bool Open(pin_t SDA, pin_t SCL, __address address)override;

	using __base::Write;
	size_t Write(ngs::byte_ptr_cst data, size_t size) override;
	using __base::Read;
	size_t Read(ngs::byte_ptr data, size_t size)override;

protected:

};


NGS_END
