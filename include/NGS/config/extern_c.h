#pragma once

#include "./defined.h"

#if NGS_CPP_VERSION

#define NGS_C       extern "C"
#define NGS_C_BEGIN extern "C" {
#define NGS_C_END   };

#else

#define NGS_C       
#define NGS_C_BEGIN 
#define NGS_C_END   

#endif