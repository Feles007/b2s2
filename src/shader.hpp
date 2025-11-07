#pragma once

#include <cmft/core.hpp>

struct ShaderProgram {
	u32 gl_handle;

	static ShaderProgram create(nt_string vertex_shader_source, nt_string fragment_shader_source);
	void use() const;
};
