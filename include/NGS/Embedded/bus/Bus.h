#pragma once

#include "NGS/Embedded/Interface.h"


NGS_BEGIN

class Bus : public EmbeddedObject {
public:
	enum class Type {
		simplex,
		half_duplex,
		full_duplex,
	};
	template<std::derived_from<Bus> T>
	static constexpr Type type = Type::simplex;

	template<std::derived_from<Bus> T>
	static constexpr bool is_simplex = type<T> == Type::simplex;

	template<std::derived_from<Bus> T>
	static constexpr bool is_half_duplex = type<T> == Type::half_duplex;

	template<std::derived_from<Bus> T>
	static constexpr bool is_full_duplex = type<T> == Type::full_duplex;


	virtual size_t Write(ngs::byte_ptr_cst data, size_t size) = 0;
	virtual bool Write(ngs::byte data) { return Write(&data, 1); }

	virtual size_t Read(ngs::byte_ptr data, size_t size) = 0;
	virtual bool Read(ngs::byte_ref data) { return Read(&data, 1); }
private:

private:

};

NGS_END
