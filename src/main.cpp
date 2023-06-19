//
// Created by 86198 on 2023/4/11.
//
#define _DEBUG
//#define NGS_USE_HPP
#include "NGS/NGS.h"

#ifdef NGS_USE_HPP
static_assert(false);
#endif


int main() {
	NGS_LOGF(ngs::debug,"ohhh %d",666);
	return 0;
}