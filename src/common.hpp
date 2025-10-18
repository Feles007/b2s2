#pragma once

#include <cstdio>
#include <cstdlib>

#define STRINGIFY(x)       STRINGIFY_INNER(x)
#define STRINGIFY_INNER(x) #x

#define FATAL_ERROR(...)          \
	do {                          \
		std::printf(__VA_ARGS__); \
		std::exit(1);             \
	} while (0)

#define xassert(expression) \
	if (!(expression)) FATAL_ERROR("Assert failed at " __FILE__ ":" STRINGIFY(__LINE__) " - xassert(" #expression ")")
