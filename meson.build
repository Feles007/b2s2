project('b2s2', 'cpp', default_options : ['warning_level=3', 'cpp_std=c++20'])

# Ignore warnings from MSVC
add_project_arguments('-D_CRT_SECURE_NO_WARNINGS', language : ['c', 'cpp'])

python = find_program('python3', 'python')

shader_generator = generator(
	python,
	output : 'shader_@BASENAME@.hpp',
	arguments : ['@SOURCE_DIR@/src/scripts/shader_gen.py', '@INPUT@', '@OUTPUT@']
)
shaders = shader_generator.process('src/shaders/vertex.glsl')

dependencies = [
	# glad
	subproject('glad').get_variable('glad'),
	# glfw
	dependency('glfw3', static : true),
]

executable(
	'b2s2',

	'src/main.cpp',
	'src/common.cpp',
	'src/allocation.cpp',
	'src/file_reader.cpp',
	shaders,

	dependencies : dependencies,
)
