#pragma once

#include "NGS/NGS.h"

#if NGS_PLATFORM != NGS_LINUX
#error "This system is not Linux. This library can only be run on Linux."
#endif

#include "NGS/nsl/defined.h"

#include "NGS/nsl/file/File.h"
#include "NGS/nsl/file/device_file.h"

#include "NGS/nsl/media/V4L2.h"

#include "NGS/nsl/media/frame_buffer.h"


#ifdef NGS_USE_HPP
#include "NGS/nsl/file/File.hpp"
#include "NGS/nsl/io/GPIO.hpp"
#include "NGS/nsl/io/MultiplexIO.hpp"
#include "NGS/nsl/media/V4L2.hpp"

#include "NGS/nsl/media/frame_buffer.hpp"

#endif
