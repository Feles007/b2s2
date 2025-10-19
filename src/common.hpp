#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#define STRINGIFY(x)       STRINGIFY_INNER(x)
#define STRINGIFY_INNER(x) #x

#define FATAL_ERROR(...)          \
	do {                          \
		std::printf(__VA_ARGS__); \
		std::putchar('\n');       \
		std::exit(1);             \
	} while (0)

#define xassert(expression) \
	if (!(expression)) FATAL_ERROR("Assert failed at " __FILE__ ":" STRINGIFY(__LINE__) " - xassert(" #expression ")")

using u8    = std::uint8_t;
using u16   = std::uint16_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using usize = std::size_t;

using i8    = std::int8_t;
using i16   = std::int16_t;
using i32   = std::int32_t;
using i64   = std::int64_t;
using isize = std::ptrdiff_t;

// Ideally null terminated strings shouldn't be
// used anywhere, but some APIs require them.
using nt_string = const char *;

void check_errno();
