//==========================================================================================================
// @file	:	NGS/NGS
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:04:40
// @brief	:	
//==========================================================================================================
#pragma once

// ==============================
// NGS:
// 1:	Version
// 2:	STL	Config
// 3:	Defined
// 4:	TypeTrait Lib Object Base 
// 5:	Bit Concepts
// 6:	Color TemplateMate ByteArray
// ==============================



#ifndef __HEAD_NGS_NGS
#define __HEAD_NGS_NGS

#include "NGS/NGS_Version.h"

#include "NGS/NGS_STL.h"
#include "NGS/NGS_Config.h"

#include "NGS/NGS_Defined.h"

#include "NGS/NGS_TypeTrait.h"
#include "NGS/NGS_Lib.h"
#include "NGS/NGS_Object.h"
#include "NGS/NGS_Base.h"

#include "NGS/NGS_Bit.h"
#include "NGS/NGS_Concepts.h"

#include "NGS/NGS_Color.h"
#include "NGS/NGS_Defined.h"
#include "NGS/ByteArray.h"

#include "NGS/NGS_Function.h"
#include "NGS/NGS_Memory.h"
#include "NGS/NGS_Setting.h"
#include "NGS/NGS_TemplateMate.h"
#include "NGS/NGS_Time.h"
#include "NGS/NGS_Debug.h"


//Math
#include "NGS/Math/Math.h"
#include "NGS/Math/Matrix.h"
#include "NGS/Math/Rectangle.h"
#include "NGS/Math/Line.h"
#include "NGS/Math/Vector.h"
//#include "NGS/Math/VectorExperiment.h"

//Debug
#include "NGS/Debug/Debug.h"
#include "NGS/Debug/Stream.h"

#include "NGS/NGS_Communication.h"

#if _MSC_VER

//#pragma comment(lib,"NGS.lib")

#endif // USE_NGS_MODULE


#endif // !__HEAD_NGS_NGS
