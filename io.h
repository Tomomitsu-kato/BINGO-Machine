#pragma once
//------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include <float.h>
#include <assert.h>

#ifndef static_assert
# define NO_STDC_STATIC_ASSERT
# define static_assert(...)
#endif // !static_assert
#if defined(_MSC_VER) || defined(_cplusplus)
# define restrict
#endif // defined(_MSC_VER) || defined(_cplusplus)

//------------------------------------------------

//------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------
static inline bool str_has_char(const char* str);
static inline bool exchange_bool(bool* restrict const io, const bool new_value);
static inline int fgets_wrap(char* restrict const s, size_t buf_size,
	FILE* restrict const fstream, const char* message_on_error);
extern inline unsigned int input_uint(const char* message, const char* restrict message_on_error,
	const unsigned int max, const unsigned int min);
//------------------------------------------------

#ifdef NO_STDC_STATIC_ASSERT
#   undef static_assert
#   undef NO_STDC_STATIC_ASSERT
#endif
