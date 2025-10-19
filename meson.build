project('b2s2', 'cpp', default_options : ['warning_level=3', 'cpp_std=c++20'])

glad = subproject('glad').get_variable('glad')
glfw = dependency('glfw3', static : true)

add_project_arguments('-D_CRT_SECURE_NO_WARNINGS', language : ['c', 'cpp'])

executable('b2s2',

		   'src/main.cpp',
		   'src/allocation.cpp',
		   'src/file_reader.cpp',

		   dependencies : [glad, glfw],
)
