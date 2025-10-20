project('b2s2', 'cpp', default_options : ['warning_level=3', 'cpp_std=c++20'])

cpp_sources = [
	'src/main.cpp',
	'src/common.cpp',
	'src/allocation.cpp',
	'src/file_reader.cpp',
	'src/shader.cpp',
]
shader_sources = [
	'src/shaders/vertex.glsl',
	'src/shaders/fragment.glsl',
]

dependencies = [
	# glad
	subproject('glad').get_variable('glad'),
	# glfw
	dependency('glfw3', static : true),
]

python = find_program('python3', 'python')

shaders = custom_target(
	'shaders',
	output : 'shader_gen.hpp',
	input : shader_sources,
	command : [python, '@CURRENT_SOURCE_DIR@/src/scripts/shader_gen.py', '@OUTPUT@', '@INPUT@'],
)

# Ignore warnings from MSVC
add_project_arguments('-D_CRT_SECURE_NO_WARNINGS', language : ['c', 'cpp'])

executable('b2s2', cpp_sources, shaders, dependencies : dependencies)
