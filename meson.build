project('b2s2', 'cpp', default_options : ['warning_level=3', 'cpp_std=c++20'])

glad = subproject('glad').get_variable('glad')
glfw = dependency('glfw3', static : true)

executable('b2s2', 'src/main.cpp', dependencies : [glad, glfw])
