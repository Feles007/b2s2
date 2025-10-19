#include "common.hpp"

#include <cerrno>
#include <cstring>

void check_errno() {
	const int e = errno;
	FATAL_ERROR("errno: %d - %s", e, std::strerror(e));
}
