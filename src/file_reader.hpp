#pragma once

#include "common.hpp"

struct FileData {
	u8 *data;
	usize length;

	static FileData read_file(nt_string path);
	static void deallocate(FileData fd);
};
