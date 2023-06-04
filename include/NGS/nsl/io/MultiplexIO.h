#pragma once

#include "NGS/nsl/defined.h"

NSL_BEGIN

class File;

class MultIO {
	template<class T>
	using Container = std::vector<T>;
public:
	NGS_FLAG(F_IN, 0);
	NGS_FLAG(F_PRI, 1);
	NGS_FLAG(F_OUT, 2);
	NGS_FLAG(F_ERR, 3);
	NGS_FLAG(F_HUP, 4);
	NGS_FLAG(F_NVAL, 5);
	NGS_FLAG(F_RDNORM, 6);
	NGS_FLAG(F_RDBAND, 7);
	NGS_FLAG(F_WRNORM, 8);
	NGS_FLAG(F_WRBAND, 9);
	NGS_FLAG(F_MSG, 10);
	NGS_FLAG(F_REMOVE, 12);
	NGS_FLAG(F_RDHUP, 13);

	using Tag = BitSet<16>;
private:
	NGS_TYPE_DEFINE(File, file);
	using ___element = std::tuple<__file_ptr_cst, Tag, Tag>;
	NGS_TYPE_DEFINE(___element, element);
public:
	void Add(__file_ptr_cst file, Tag tag) { _files.emplace_back(std::make_tuple(file, tag, Tag{})); }

	int Poll(int timeout);

	const Container<__element>& GetFiles()const { return _files; }
private:

private:
	Container < __element> _files;
	ngs::void_ptr _data = nullptr;
};

NSL_END
