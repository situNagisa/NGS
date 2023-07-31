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

	enum class Flag : byte {
		write = 0,
		read = 1,
	};

	static constexpr __address null_address = 0;
public:
	I2C();
	virtual ~I2C()override;

	/**
	 * @brief open i2c bus
	 *
	 * @param SDA
	 * @param SCL
	 * @param address
	 * @return
	 *		- true: success
	 *		- false: failed
	 */
	virtual bool Open(pin_t SDA, pin_t SCL, __address address) = 0;
	/**
	 * @brief open i2c bus with default address(null_address)
	 *
	 * @see I2C::Open(pin_t SDA, pin_t SCL, __address address)
	 * @see I2C::null_address
	 *
	 * @param SDA
	 * @param SCL
	 * @return
	 *		- true: success
	 *		- false: failed
	 */
	bool Open(pin_t SDA, pin_t SCL) { return Open(SDA, SCL, null_address); }

	/**
	 * @brief is opened or not
	 *
	 * @return
	 *		-true: opened
	 *		-false: not opened
	 */
	bool IsOpened()const override;
	/**
	 * @brief close i2c bus
	 *
	 */
	virtual void Close()override;

	/**
	 * @brief enable 10bit address mode
	 *
	 * @param enable
	 */
	void Enable10bitAddress(bool enable) { _mask = enable ? BitSet<10>::Mask : BitSet<7>::Mask; }
	/**
	 * @brief set address
	 *
	 * @param address
	 */
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
		// it is UB if you don't distinguish the const pointer
		union {
			void_ptr_cst write = nullptr;
			void_ptr read;
		}data;
		size_t count{};
		void_ptr user_data = nullptr;
	};
	using __base::Open;
	/**
	 * @brief open i2c bus
	 *
	 * @param SDA
	 * @param SCL
	 * @param address
	 * @return
	 *		- true: success
	 * 		- false: failed
	 */
	bool Open(pin_t SDA, pin_t SCL, __address address)override;

	/**
	 * @brief set ack
	 *
	 * @see I2CMaster::ACK_Type
	 *
	 * @param ack is ack
	 * @param type ack type
	 */
	void SetACK(bool ack, ACK_Type type) { _ack = { ack,type }; }

	using __base::Write;
	/**
	 * @brief write data
	 *
	 * @param data
	 * @param count
	 * @return
	 *		- > 0: success(It doesn't have to be write count, but try to make sure)
	 *		- 0: failed
	 */
	size_t Write(byte_ptr_cst data, size_t count) override {
		Message message = {};
		message.flag = Flag::write;
		message.data.write = data;
		message.count = count;
		return Transfer(message);
	}
	using __base::Read;
	size_t Read(byte_ptr data, size_t count)override {
		Message message = {};
		message.flag = Flag::read;
		message.data.read = data;
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
