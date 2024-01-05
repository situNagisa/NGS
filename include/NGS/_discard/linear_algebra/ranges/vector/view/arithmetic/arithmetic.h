#pragma once

#define NGS_MATH_VECTOR_ARITHMETIC_ID add
#define NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID addable
#define NGS_MATH_VECTOR_ARITHMETIC_OP +
#include "./gen.h"

#define NGS_MATH_VECTOR_ARITHMETIC_ID subtract
#define NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID subtractable
#define NGS_MATH_VECTOR_ARITHMETIC_OP -
#include "./gen.h"

#define NGS_MATH_VECTOR_ARITHMETIC_ID multiply
#define NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID multipliable
#define NGS_MATH_VECTOR_ARITHMETIC_OP *
#include "./gen.h"

#define NGS_MATH_VECTOR_ARITHMETIC_ID divide
#define NGS_MATH_VECTOR_ARITHMETIC_CONCEPT_ID divisible
#define NGS_MATH_VECTOR_ARITHMETIC_OP /
#include "./gen.h"