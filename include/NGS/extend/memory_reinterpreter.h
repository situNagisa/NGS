#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/concepts.h"
#include "NGS/extend/meta_variable_wrapper.h"

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/reverse_iterator.hpp>

NGS_BEGIN

template<mpl::CMetaStruct _MetaStruct, class = std::make_index_sequence<mpl::spread_struct_t<_MetaStruct>::count>>
class NGS_API MemoryReinterpreter;

/**
 * @brief 按元结构体所描述的内存重解释
 *	
 * @concept ngs::mpl::CMetaStruct
 * 
 * @tparam _MetaStruct 元结构体，用于描述内存布局
 * 
 * @warning 重解释的内存必须是有效的，且不能有内存对齐，否则行为未定义
 */
template<mpl::CMetaStruct _MetaStruct, size_t ..._VarIndex>
class NGS_API MemoryReinterpreter < _MetaStruct, std::index_sequence< _VarIndex...>> {
protected:
	using self_type = MemoryReinterpreter;
public:
	using meta_struct_type = mpl::spread_struct_t<_MetaStruct>;
	template<size_t _Index> using var = typename meta_struct_type::template variable_at<_Index>;
	constexpr static size_t memory_size = meta_struct_type::size;

	constexpr MemoryReinterpreter(void_ptr memory)
		: _memory(static_cast<byte_ptr>(memory))
	{}

	constexpr void Rebind(void_ptr memory){
		_memory = static_cast<byte_ptr>(memory);
	}
	/**
	 * @brief 获取变量
	 * 
	 * @tparam _Index 变量索引
	 * 
	 * @return 
	 */
	template<size_t _Index>
	constexpr auto Get() {
		using v = var<_Index>;
		using e = typename var<_Index>::element_type;
		auto p = std::launder(reinterpret_cast<e*>(_memory + meta_struct_type::variables[_Index].offset));
		return meta_variable_wrapper<v,ccpt::bool_<false>>(p);
	}
	template<size_t _Index>
	constexpr auto Get()const {
		using v = var<_Index>;
		using e = typename var<_Index>::element_type;
		auto p = std::launder(reinterpret_cast<const e*>(_memory + meta_struct_type::variables[_Index].offset));
		return meta_variable_wrapper<v,ccpt::bool_<true>>(p);
	}

	template<class _Type>
	constexpr _Type* Get(size_t index) {
		return std::launder(reinterpret_cast<_Type*>(_memory + meta_struct_type::variables[index].offset));
	}
	template<class _Type>
	constexpr const _Type* Get(size_t index)const {
		return std::launder(reinterpret_cast<const _Type*>(_memory + meta_struct_type::variables[index].offset));
	}

	constexpr byte_ptr Get(size_t index) { return Get<byte>(index); }
	constexpr byte_ptr_cst Get(size_t index)const { return Get<byte>(index); }

	constexpr size_t GetSize()const { return meta_struct_type::size; }
	constexpr size_t GetVariableCount()const { return meta_struct_type::count; }

	//=============
	// range
	//=============

	constexpr size_t size() const { return GetVariableCount(); }
private:
	template<bool _Constant>
	struct NGS_API _Iterator : boost::stl_interfaces::iterator_interface <
		_Iterator<_Constant>,
		std::random_access_iterator_tag,
		byte_ptr
	> {
	protected:
		using _base_type = boost::stl_interfaces::iterator_interface<
			_Iterator<_Constant>,
			std::random_access_iterator_tag,
			byte_ptr
		>;
		using _self_type = _Iterator;
		using _element_type = std::conditional_t<_Constant, byte_ptr_cst, byte_ptr>;
		using _iterator_type = _self_type;

		using _expression_ptr = std::conditional_t<_Constant, const self_type*, self_type*>;
		using _difference_type = typename _base_type::difference_type;
	public:
		using _base_type::_base_type;
		constexpr _Iterator(_expression_ptr expr, _difference_type n) : _expr(expr), _n(n) {}
		constexpr _Iterator(_expression_ptr expr) : _Iterator(expr, 0) {}

		constexpr _element_type operator*()const {
			return _expr->Get(_n);
		}
		constexpr _iterator_type& operator+=(_difference_type n) { _n += n; return static_cast<_iterator_type&>(*this); }
		constexpr _difference_type operator-(_iterator_type other)const { return _n - other._n; }

	protected:
		_expression_ptr _expr = nullptr;
		_difference_type _n = 0;
	};
public:
	using iterator_type = _Iterator<false>;
	using const_iterator_type = _Iterator<true>;
	using reverse_iterator_type = boost::stl_interfaces::reverse_iterator<iterator_type>;
	using const_reverse_iterator_type = boost::stl_interfaces::reverse_iterator<const_iterator_type>;

	constexpr iterator_type begin() { return iterator_type(this); }
	constexpr iterator_type end() { return iterator_type(this, size()); }
	constexpr const_iterator_type begin()const { return const_iterator_type(this); }
	constexpr const_iterator_type end()const { return const_iterator_type(this, size()); }
	constexpr const_iterator_type cbegin()const { return begin(); }
	constexpr const_iterator_type cend()const { return end(); }

	constexpr reverse_iterator_type rbegin() { return reverse_iterator_type(end()); }
	constexpr reverse_iterator_type rend() { return reverse_iterator_type(begin()); }
	constexpr const_reverse_iterator_type rbegin()const { return const_reverse_iterator_type(end()); }
	constexpr const_reverse_iterator_type rend()const { return const_reverse_iterator_type(begin()); }
	constexpr const_reverse_iterator_type crbegin()const { return rbegin(); }
	constexpr const_reverse_iterator_type crend()const { return crend(); }
private:
	byte_ptr _memory;
};

template<mpl::CMetaStruct _MetaStruct, size_t ..._VarIndex>
constexpr std::string to_string(const MemoryReinterpreter<_MetaStruct, std::index_sequence<_VarIndex...>>& ptr) {
	std::string str;
	str += "{";
	bool first = true;
	((str += (first ? "" : ", ") + to_string(ptr.template Get<_VarIndex>()), first = false), ...);
	str += "}";
	return str;
}

NGS_END

namespace std {

template<size_t _Index, ngs::mpl::CMetaStruct _MetaStruct>
constexpr auto get(ngs::MemoryReinterpreter<_MetaStruct>& ptr) {
	return ptr.template get<_Index>();
}
template<class _Type, ngs::mpl::CMetaStruct _MetaStruct>
constexpr auto get(ngs::MemoryReinterpreter<_MetaStruct>& ptr, size_t index) {
	return ptr.template get<_Type>(index);
}
template<ngs::mpl::CMetaStruct _MetaStruct>
constexpr auto get(ngs::MemoryReinterpreter<_MetaStruct>& ptr, size_t index) {
	return ptr.get(index);
}

template<size_t _Index, ngs::mpl::CMetaStruct _MetaStruct>
constexpr auto get(const ngs::MemoryReinterpreter<_MetaStruct>& ptr) {
	return ptr.template get<_Index>();
}
template<class _Type, ngs::mpl::CMetaStruct _MetaStruct>
constexpr auto get(const ngs::MemoryReinterpreter<_MetaStruct>& ptr, size_t index) {
	return ptr.template get<_Type>(index);
}
template<ngs::mpl::CMetaStruct _MetaStruct>
constexpr auto get(const ngs::MemoryReinterpreter<_MetaStruct>& ptr, size_t index) {
	return ptr.get(index);
}

}