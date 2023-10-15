#pragma once

#include "../defined.h"

NGS_MATH_BEGIN

constexpr double power(double base, int x)
{
    if (std::is_constant_evaluated() && !(base == 0.0 && x < 0)) {
        // 常量求值语境：使用 constexpr 友好的算法。
        if (x == 0)
            return 1.0;
        double r = 1.0, p = x > 0 ? base : 1.0 / base;
        auto u = static_cast<unsigned>(x > 0 ? x : -x);
        while (u != 0) {
            if (u & 1) r *= p;
            u /= 2;
            p *= p;
        }
        return r;
    }
    else {
        // 令代码生成器生成。
        return std::pow(base, static_cast<double>(x));
    }
}

NGS_MATH_END
