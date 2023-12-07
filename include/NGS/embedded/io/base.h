#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

/**
 * \brief io流抽象基类
*/
struct NGS_DLL_API basic_io
{
protected:
	using self_type = basic_io;
public:
	virtual ~basic_io() = default;

	/**
	 * \brief io流是否打开
	 * \return true 打开，false 关闭
	 */
	virtual bool is_opened() const = 0;

	/**
	 * \brief 关闭io流
	 */
	virtual void close() = 0;
	/**
	 * \brief 从io流中读取数据
	 * \param buffer 缓存区
	 * \param size 需要读取的长度（0为默认）
	 * \return 读取成功的数据
	 */
	virtual size_t read(void_ptr buffer, size_t size = 0) = 0;
	/**
	 * \brief 将数据写入到io流中
	 * \param buffer 缓存区
	 * \param size 需要写入的长度
	 * \return 写入成功的数据
	 */
	virtual size_t write(void_ptr_cst buffer, size_t size) = 0;

	NGS_CONSTEXPR26 size_t write(::std::ranges::contiguous_range auto&& buffer)
	{
		return this->write(::std::ranges::data(NGS_PP_PERFECT_FORWARD(buffer)), ::std::ranges::size(buffer));
	}
	NGS_CONSTEXPR26 size_t write(::std::convertible_to<byte> auto&&... buffer)
	{
		std::array<byte, sizeof...(buffer)> b{ static_cast<byte>(NGS_PP_PERFECT_FORWARD(buffer))... };
		return this->write(b);
	}
	NGS_CONSTEXPR26 size_t read(::std::ranges::contiguous_range auto& buffer)
	{
		return this->read(::std::ranges::data(buffer), ::std::ranges::size(buffer));
	}
};

NGS_LIB_END