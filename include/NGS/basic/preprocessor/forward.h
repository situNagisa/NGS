#pragma once

#define NGS_PERFECT_FORWARD(x) ::std::forward<decltype((x))>(x)