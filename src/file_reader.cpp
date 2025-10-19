#include <cstdio>

#include "allocation.hpp"
#include "file_reader.hpp"

FileData FileData::read_file(nt_string path) {
	std::FILE *file = std::fopen(path, "rb");
	if (!file) check_errno();

	auto result_fseek = std::fseek(file, 0, SEEK_END);
	if (result_fseek) check_errno();

	const auto file_size_long = std::ftell(file);
	if (file_size_long == -1) check_errno();
	const auto file_size = static_cast<usize>(file_size_long);

	u8 *buffer = allocate_array<u8>(file_size);

	std::rewind(file);

	auto result_fread = std::fread(buffer, 1, file_size, file);
	if (result_fread != file_size) {
		// Weird racy situation where the whole
		// file was read but the size has changed.
		xassert(!std::feof(file));

		check_errno();
	}

	auto result_fclose = std::fclose(file);
	if (result_fclose) check_errno();

	return {.data = buffer, .length = file_size};
}
void FileData::deallocate(FileData fd) {
	deallocate_array(fd.data, fd.length);
}
