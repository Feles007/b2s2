#pragma once

#include "common.hpp"
#include <glad/glad.h>

struct VertexShader {
	u32 gl_handle;

	static VertexShader compile(nt_string source);
};
struct FragmentShader {
	u32 gl_handle;

	static FragmentShader compile(nt_string source);
};
struct ShaderProgram {
	u32 gl_handle;

	static ShaderProgram create(VertexShader vertex_shader, FragmentShader fragment_shader);
	void use();
};
