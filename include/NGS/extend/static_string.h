#pragma once

#include "NGS/base/base.h"

#include <boost/static_string/static_string.hpp>

NGS_BEGIN

template<std::size_t _N, class _CharType, class _Traits = std::char_traits<_CharType>>
struct basic_static_string {
protected:
	using self_type = basic_static_string;
	using closure_type = self_type&;
	using const_closure_type = const self_type&;
public:
	using traits_type = _Traits;
	using value_type = _CharType;

	using size_type = std::size_t;
	using difference_type = size_type;

	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;
private:
	template<bool _Constant>
	struct _Iterator :
		boost::stl_interfaces::iterator_interface<_Iterator<_Constant>, std::random_access_iterator_tag,
		std::conditional_t<_Constant, std::add_const_t<value_type>, value_type>
		> {
	private:
		using base_type = boost::stl_interfaces::iterator_interface < _Iterator<_Constant>, std::random_access_iterator_tag,
			std::conditional_t<_Constant, std::add_const_t<value_type>, value_type>>;
	public:
		NGS_minherit_t(value_type, base_type);
		NGS_minherit_t(pointer, base_type);
		NGS_minherit_t(reference, base_type);
		NGS_minherit_t(difference_type, base_type);
		//NGS_minherit_t(size_type, base_type);

		using base_type::base_type;
		constexpr explicit(false) _Iterator(pointer _ptr) noexcept :_ptr(_ptr) {}

		constexpr reference operator*()const { return *_ptr; }
		constexpr _Iterator& operator+=(size_type _offset) noexcept { _ptr += _offset; return *this; }
		constexpr difference_type operator-(_Iterator _other)const noexcept { return _ptr - _other._ptr; }
	private:
		pointer _ptr = nullptr;
	};
public:
	using iterator = _Iterator<false>;
	using const_iterator = _Iterator<true>;
	using reverse_iterator = boost::stl_interfaces::reverse_iterator<iterator>;
	using const_reverse_iterator = boost::stl_interfaces::reverse_iterator<const_iterator>;

	constexpr static size_type char_size = _N;
	constexpr static size_type npos = (-1);

	constexpr explicit(false) basic_static_string(const value_type(&str)[_N]) noexcept {
		assign(str);
		/*for (size_t i = 0; i < char_size; i++)
		{
			source[i] = str[i];
		}*/
	}

	constexpr iterator begin()noexcept { return source; }
	constexpr const_iterator begin()const noexcept { return source; }
	constexpr const_iterator cbegin()const noexcept { return source; }
	constexpr iterator end()noexcept { return source + char_size; }
	constexpr const_iterator end()const noexcept { return source + char_size; }
	constexpr const_iterator cend()const noexcept { return source + char_size; }
	constexpr reverse_iterator rbegin()noexcept { return reverse_iterator(end()); }
	constexpr const_reverse_iterator rbegin()const noexcept { return const_reverse_iterator(end()); }
	constexpr const_reverse_iterator crbegin()const noexcept { return const_reverse_iterator(end()); }
	constexpr reverse_iterator rend()noexcept { return reverse_iterator(begin()); }
	constexpr const_reverse_iterator rend()const noexcept { return const_reverse_iterator(begin()); }
	constexpr const_reverse_iterator crend()const noexcept { return const_reverse_iterator(begin()); }

	/**
	 * \brief  以 char_size 个 ch 的副本替换内容。
	 *
	 * \param ch 用以初始化字符串的字符的值
	 * \return
	 */
	constexpr closure_type assign(value_type ch) {
		for (std::size_t i = 0; i < char_size; ++i) {
			traits_type::assign(source[i], ch);
		}
		return *this;
	}
	/**
	 * \brief 以 str 的副本替换内容。等价于 *this = str; 。
	 *
	 * \param str 用作源以初始化字符的 string
	 * \return
	 */
	constexpr closure_type assign(const_closure_type str) {
		for (std::size_t i = 0; i < char_size; ++i) {
			traits_type::assign(source[i], str[i]);
		}
		return *this;
	}
	/**
	 * \brief 以 str 的子串 [pos, pos+count) 替换内容。若请求的子串越过 string 尾，或若 count == char_size ，则产生的子串是 [pos, str.size()) 。
	 *
	 * \param str 用作源以初始化字符的 string
	 * \param pos 要取的首字符下标
	 * \param count  产生的 string 大小
	 * \return
	 */
	constexpr closure_type assign(const_closure_type str, size_type pos, size_type count = npos) {
		static_assert(pos <= size(), "pos out of range");
		count = (pos + count > char_size) ? char_size - pos : count;
		for (std::size_t i = pos; i < count; ++i) {
			traits_type::assign(source[i], str[i]);
		}
		return *this;
	}
	/**
	 * \brief 以 str 的副本替换内容。等价于 *this = str; 。
	 *
	 * \param str 用作源以初始化字符的 string
	 * \return
	 */
	constexpr closure_type assign(const value_type(&str)[char_size]) noexcept {
		for (std::size_t i = 0; i < char_size; ++i) {
			traits_type::assign(source[i], str[i]);
			//source[i] = str[i];
		}
		return *this;
	}

	/**
	 * \brief 返回到位于指定位置 pos 的字符的引用
	 *
	 * \param pos 要返回的字符位置
	 * \return 到请求的字符的引用。
	 */
	constexpr reference at(size_type pos) { return source[pos]; }
	constexpr const_reference at(size_type pos)const { return source[pos]; }

#if NGS_COMPILER == NGS_MSVC
#pragma warning(push)
#pragma warning(disable: 4172)
#endif
	/**
	 * \brief 在 pos < size() 时返回到位于指定位置 pos 的字符的引用，或在 pos == size() 时返回到拥有值 CharT() 的字符（空字符）的引用。不进行边界检查。
	 * 如果 pos > size()，那么行为未定义。
	 *
	 * \warning 对于重载 (1)，如果 pos == size()，那么返回的引用指代的对象被修改成 CharT() 以外的值的 (C++11 起)行为未定义。
	 *
	 * \param pos 要返回的字符位置
	 * \return 在 pos < size() 时返回 *(begin() + pos)，或在 pos == size() 时返回到 CharT() 的引用。
	 */
	constexpr reference operator[](size_type pos) {
		if (pos < size()) {
			return *(begin() + pos);
		}
		return value_type();
	}
	constexpr const_reference operator[](size_type pos)const {
		if (pos < size()) {
			return *(begin() + pos);
		}
		return value_type();
	}
#if NGS_COMPILER == NGS_MSVC
#pragma warning(pop)
#endif
	/**
	 * \brief 返回到 string 中首字符的引用。若 empty() == true 则行为未定义
	 *
	 * \return 到首字符的引用，等价于 operator[](0) 。
	 */
	constexpr reference front() { return (*this)[0]; }
	constexpr const_reference front()const { return (*this)[0]; }

	/**
	 * \brief 返回字符串中的末字符。若 empty() == true 则行为未定义。
	 *
	 * \return 到末字符的引用，等价于 operator[](size() - 1) 。
	 */
	constexpr reference back() { return (*this)[size() - 1]; }
	constexpr const_reference back()const { return (*this)[size() - 1]; }

	constexpr pointer data()noexcept { return std::addressof((*this)[0]); }
	constexpr const_pointer data()const noexcept { return std::addressof((*this)[0]); }

	constexpr pointer c_str()noexcept { return data(); }
	constexpr const_pointer c_str()const noexcept { return data(); }

	constexpr operator std::basic_string_view<value_type, traits_type>()const noexcept { return std::basic_string_view<value_type, traits_type>(data(), size()); }

	constexpr size_type size()const { return std::distance(begin(), end()); }
	constexpr size_type length()const { return size(); }

	constexpr bool empty()const noexcept { return begin() == end(); }

	constexpr size_type max_size()const noexcept { return char_size; }

	constexpr operator std::basic_string<value_type, traits_type>()const {
		return std::basic_string<value_type, traits_type>(begin(), end());
	}
public:
	value_type source[char_size];
};

template<std::size_t _N>
using static_string = basic_static_string<_N, char, std::char_traits<char>>;
template<std::size_t _N>
using static_wstring = basic_static_string<_N, wchar_t, std::char_traits<wchar_t>>;
template<std::size_t _N>
using static_u16string = basic_static_string<_N, char16_t, std::char_traits<char16_t>>;
template<std::size_t _N>
using static_u32string = basic_static_string<_N, char32_t, std::char_traits<char32_t>>;
template<std::size_t _N>
using static_u8string = basic_static_string<_N, char8_t, std::char_traits<char8_t>>;

//template<size_t _N,class _CharType>
//basic_static_string(_CharType(&)[_N]) -> basic_static_string<_N, std::decay_t<_CharType>>;

//template<size_t _N>
//constexpr std::string to_string(const static_string<_N>& str) { return std::string(str.source); }

NGS_END