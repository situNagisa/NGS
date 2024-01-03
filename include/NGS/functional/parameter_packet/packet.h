#pragma once

#include "./packet/concept.h"
#include "./packet/unpack.h"
#include "./packet/packet.h"
#include "./packet/make.h"
#include "./packet/replace.h"

NGS_LIB_MODULE_EXPORT(packet);
NGS_LIB_MODULE_EXPORT(packet_like);
NGS_LIB_MODULE_EXPORT(make_packet);

#include "NGS/lib/module_end.h"