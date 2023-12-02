#pragma once

#include "./concept.h"

NGS_LIB_MODULE_BEGIN

template<CStructureDescribe _Describe>
struct alignas(_Describe::align) struct_storage : _Describe {
protected:
	using self_type = struct_storage;
public:
	using describe_type = _Describe;

	constexpr struct_storage() = default;

	template<class _Type>
		requires (sizeof(_Type) == describe_type::size)
	constexpr struct_storage& operator=(const _Type& obj) {
		std::memcpy(data, &obj, describe_type::size);
		return *this;
	}

	//template<class _Type>
	//	requires (sizeof(_Type) == describe_type::size)
	//explicit(true) constexpr operator _Type& () {
	//	return *reinterpret_cast<_Type*>(data);
	//}

	template<size_t _Index>
	constexpr auto&& get() {
		constexpr auto variables = describe_type::get_variables();
		using variable_type = typename describe_type::template variable_at<_Index>;
		return *(reinterpret_cast<typename variable_type::storage_type*>(data + variables[_Index].offset));
	}
	template<size_t _Index>
	constexpr auto&& get()const {
		constexpr auto variables = describe_type::get_variables();
		using variable_type = typename describe_type::template variable_at<_Index>;
		return *(reinterpret_cast<const typename variable_type::storage_type*>(data + variables[_Index].offset));
	}

	constexpr auto get(size_t index) {
		constexpr auto variables = describe_type::get_variables();
		return data + variables[index].offset;
	}
	constexpr auto get(size_t index) const {
		constexpr auto variables = describe_type::get_variables();
		return data + variables[index].offset;
	}
	constexpr auto get_size(size_t index) const {
		constexpr auto variables = describe_type::get_variables();
		return variables[index].size;
	}
	constexpr auto get_span(size_t index) {
		return std::span{ get(index), get_size(index) };
	}
	constexpr auto get_span(size_t index)const {
		return std::span{ get(index), get_size(index) };
	}
	//====================
	// range
	//====================
	template<bool _Constant>
	struct _storage_iterator :
		nboost::stl_interfaces::base_random_access_iterator<
		_storage_iterator<_Constant>,
		std::span<std::conditional_t<_Constant, const byte, byte>>
		>
	{
		NGS_MPL_ENVIRON2(_storage_iterator, nboost::stl_interfaces::base_random_access_iterator<_storage_iterator<_Constant>, std::span<std::conditional_t<_Constant, const byte, byte>>>);
	public:
		NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
		NGS_MPL_INHERIT_TYPE(value_type, base_type);
		NGS_MPL_INHERIT_TYPE(reference, base_type);
		NGS_MPL_INHERIT_TYPE(pointer, base_type);
		NGS_MPL_INHERIT_TYPE(difference_type, base_type);

		using range_type = std::conditional_t<_Constant, const struct_storage, struct_storage>;
	public:
		using base_type::base_type;
		constexpr _storage_iterator(range_type* range, size_t size)
			: _range(range)
			, _index(size)
		{}
		constexpr _storage_iterator() = default;

		constexpr iterator_type& operator+=(difference_type n) {
			_index += n;
			return base_type::_derived();
		}
		constexpr difference_type operator-(self_type other)const { return other._index - _index; }

		constexpr value_type operator*()const {
			return { _range->get(_index), _range->get_size(_index) };
		}
	private:
		range_type* _range = nullptr;
		size_t _index = 0;
	};

	using io_iterator_type = _storage_iterator<false>;
	using in_iterator_type = _storage_iterator<true>;
	using reverse_io_iterator_type = std::reverse_iterator<io_iterator_type>;
	using reverse_in_iterator_type = std::reverse_iterator<in_iterator_type>;

	constexpr auto begin() { return io_iterator_type{ this,0 }; }
	constexpr auto begin()const { return in_iterator_type{ this,0 }; }
	constexpr auto end() { return io_iterator_type{ this, describe_type::variable_count }; }
	constexpr auto end()const { return in_iterator_type{ this, describe_type::variable_count }; }

	constexpr auto rbegin() { return reverse_io_iterator_type{ end() }; }
	constexpr auto rbegin()const { return reverse_in_iterator_type{ end() }; }
	constexpr auto rend() { return reverse_io_iterator_type{ begin() }; }
	constexpr auto rend()const { return reverse_in_iterator_type{ begin() }; }

	constexpr auto cbegin()const { return begin(); }
	constexpr auto cend()const { return end(); }
	constexpr auto crbegin()const { return rbegin(); }
	constexpr auto crend()const { return rend(); }
public:
	byte data[describe_type::size]{};
};

NGS_LIB_MODULE_END

NGS_BEGIN

template<mpl::mstruct::CStructureStorage _Struct>
constexpr std::string to_string(const _Struct& s) {
	std::string str{};
	str += "{";
	str += [&s]<size_t... _Index>(std::index_sequence<_Index...>) {
		std::string str{};
		bool first = true;
		((str += (first ? "" : ", ") + to_string(s.template get<_Index>()), first = false), ...);
		return str;
	}(std::make_index_sequence<_Struct::variable_count>{});
	str += "}";
	return str;
}

NGS_END
