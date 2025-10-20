#include "shader.hpp"
#include "allocation.hpp"
#include "common.hpp"
#include <glad/glad.h>

u32 build_shader(GLenum shader_type, nt_string source) {
	const u32 shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	i32 status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status) return shader;

	// Error case
	i32 log_size;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);

	auto log_buffer = allocate_array<char>(log_size);
	glGetShaderInfoLog(shader, log_size, nullptr, log_buffer);

	FATAL_ERROR_DEFER_EXIT("Error compiling shader - %s", log_buffer);
	deallocate_array(log_buffer, log_size);
	EXIT();
}

VertexShader VertexShader::compile(nt_string source) {
	return {.gl_handle = build_shader(GL_VERTEX_SHADER, source)};
}
FragmentShader FragmentShader::compile(nt_string source) {
	return {.gl_handle = build_shader(GL_FRAGMENT_SHADER, source)};
}
