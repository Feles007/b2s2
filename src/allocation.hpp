#pragma once

#include "common.hpp"

struct Layout {
	usize size;
	usize alignment;

	template <typename T>
	static Layout of_type() {
		return {.size = sizeof(T), .alignment = alignof(T)};
	}

	template <typename T>
	static Layout of_array(usize length) {
		Layout layout = of_type<T>();
		layout.size *= length;
		return layout;
	}
};

void *allocate(Layout layout);
void deallocate(void *ptr, Layout layout);

template <typename T>
T *allocate_single() {
	return static_cast<T *>(allocate(Layout::of_type<T>()));
}
template <typename T>
void deallocate_single(T *ptr) {
	deallocate(ptr, Layout::of_type<T>());
}
template <typename T>
T *allocate_array(usize length) {
	return static_cast<T *>(allocate(Layout::of_array<T>(length)));
}
template <typename T>
void deallocate_array(T *ptr, usize length) {
	deallocate(ptr, Layout::of_array<T>(length));
}
