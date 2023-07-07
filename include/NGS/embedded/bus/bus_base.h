#pragma once

#include "NGS/embedded/interface.h"


NGS_BEGIN

class BusBase : public EmbeddedObject {
public:
	enum class Type {
		simplex,
		half_duplex,
		full_duplex,
	};
	static constexpr Type type = Type::simplex;

	template<std::derived_from<BusBase> T>
	static constexpr bool is_simplex = T::type == Type::simplex;

	template<std::derived_from<BusBase> T>
	static constexpr bool is_half_duplex = T::type == Type::half_duplex;

	template<std::derived_from<BusBase> T>
	static constexpr bool is_full_duplex = T::type == Type::full_duplex;


	virtual size_t Write(ngs::byte_ptr_cst data, size_t size) = 0;
	virtual bool Write(ngs::byte data) { return Write(&data, 1); }

	virtual size_t Read(ngs::byte_ptr data, size_t size) = 0;
	virtual bool Read(ngs::byte_ref data) { return Read(&data, 1); }
private:

private:

};

template<BusBase::Type _Type>
class BusSync : public BusBase {
public:
	static constexpr typename BusBase::Type type = _Type;
};

template<BusBase::Type _Type>
class BusAsync : public BusBase {
	static constexpr typename BusBase::Type type = _Type;
};

NGS_END
