#include "allocation.hpp"

void *allocate(Layout layout) {
	void *p = _aligned_malloc(layout.size, layout.alignment);
	if (p) return p;
	FATAL_ERROR("Allocation of %zu:%zu failed", layout.size, layout.alignment);
}
void deallocate(void *p, [[maybe_unused]] Layout layout) {
	if (p) _aligned_free(p);
	FATAL_ERROR("Null pointer freed");
}
