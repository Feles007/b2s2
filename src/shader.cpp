#include "shader.hpp"
#include "allocation.hpp"
#include "common.hpp"
#include <glad/glad.h>

u32 build_shader(GLenum shader_type, nt_string source) {
	const auto shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	i32 status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status) return shader;

	i32 log_size;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);

	const auto log_buffer = allocate_array<char>(log_size);
	glGetShaderInfoLog(shader, log_size, nullptr, log_buffer);

	FATAL_ERROR_DEFER_EXIT("Error compiling shader - %s", log_buffer);
	deallocate_array(log_buffer, log_size);
	EXIT();
}
ShaderProgram ShaderProgram::create(nt_string vertex_shader_source, nt_string fragment_shader_source) {
	const auto vertex_shader   = build_shader(GL_VERTEX_SHADER, vertex_shader_source);
	const auto fragment_shader = build_shader(GL_FRAGMENT_SHADER, vertex_shader_source);

	const auto shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	i32 status;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &status);

	if (status) return {.gl_handle = shader_program};

	i32 log_size;
	glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_size);

	const auto log_buffer = allocate_array<char>(log_size);
	glGetShaderInfoLog(shader_program, log_size, nullptr, log_buffer);

	FATAL_ERROR_DEFER_EXIT("Error building shader program - %s", log_buffer);
	deallocate_array(log_buffer, log_size);
	EXIT();
}
void ShaderProgram::use() const {
	glUseProgram(gl_handle);
}
