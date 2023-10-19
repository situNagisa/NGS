#pragma once

#include "./defined.h"

NGS_BEGIN

#if NGS_COMPILER == NGS_MSVC
#pragma warning(push)
#pragma warning(disable: 6011)
#endif

/**
 * \brief һ������£����ǲ���ʹ�������������������������ڱ����ڻ�ȡһ�����͵�ֵ��
 *
 * \warning �˺���Ӧ��`decltype`�ؼ��ִ���ʹ�ã�����Ӧ�õ����������ûᵼ��δ������Ϊ
 *
 * \return һ�����͵�ֵ
*/
template<class _Type>
constexpr std::add_rvalue_reference_t<_Type> declval() {
	_Type* ptr = nullptr;
	return std::move(*ptr);
}

#if NGS_COMPILER == NGS_MSVC
#pragma warning(pop)
#endif

NGS_END