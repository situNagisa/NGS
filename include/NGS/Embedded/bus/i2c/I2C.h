#pragma once

#include "NGS/base/base.h"
#include "NGS/embedded/bus/bus_base.h"

NGS_BEGIN

class I2C : public BusSync<BusBase::Type::half_duplex> {
protected:
	NGS_TYPE_DEFINE(ngs::uint16, address);
	NGS_TYPE_DEFINE(I2C, base);

public:
	using address_type = __address;

	enum class Flag {
		write = 0,
		read = 1,
	};

	static constexpr __address null_address = 0;
public:
	I2C();
	virtual ~I2C()override;

	virtual bool Open(pin_t SDA, pin_t SCL, __address address) = 0;
	bool Open(pin_t SDA, pin_t SCL) { return Open(SDA, SCL, null_address); }

	bool IsOpened()const override;
	virtual void Close()override;

	void Enable10bitAddress(bool enable) { _mask = enable ? BitSet<10>::Mask : BitSet<7>::Mask; }
	void SetAddress(__address address) { _address = address & _mask; }
protected:
	__address _AddressWrite()const { return (_address << 1) | (int)Flag::write; }
	__address _AddressRead()const { return (_address << 1) | (int)Flag::read; }

protected:
	__address _mask = bit::mask(7);
	__address _address = null_address;
};


class I2CMaster : public I2C {
public:
	enum class ACK_Type {
		ack = 0x0,			/*!< I2C ack for each byte read */
		nack = 0x1,			/*!< I2C nack for each byte read */
		last_nack = 0x2,	/*!< I2C nack for the last byte*/
		max,
	};
public:
	struct Message {
		Flag flag{};
		void_ptr_cst data = nullptr;
		size_t count{};
		void_ptr user_data = nullptr;
	};
	using __base::Open;
	bool Open(pin_t SDA, pin_t SCL, __address address)override;

	void SetACK(bool ack, ACK_Type type) { _ack = { ack,type }; }

	using __base::Write;
	size_t Write(byte_ptr_cst data, size_t count) override {
		Message message = {};
		message.flag = Flag::write;
		message.data = data;
		message.count = count;
		return Transfer(message);
	}
	using __base::Read;
	size_t Read(byte_ptr data, size_t count)override {
		Message message = {};
		message.flag = Flag::read;
		message.data = data;
		message.count = count;
		return Transfer(message);
	}
	size_t WriteRead(byte_ptr_cst write_data, size_t write_count, byte_ptr read_data, size_t read_count) {
		Message message[] = { {
				Flag::write,
				write_data,
				write_count
			},{
				Flag::read,
				read_data,
				read_count
			}
		};
		return Transfer(message);
	}

	size_t Transfer(const Message* messages, size_t count);
	size_t Transfer(const Message& message) { return Transfer(&message, 1); }
	template<std::ranges::random_access_range _Rng>
		requires std::convertible_to<std::ranges::range_value_t<_Rng>, Message>
	size_t Transfer(const _Rng& messages) { return Transfer(std::ranges::cdata(messages), std::ranges::size(messages)); }
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
