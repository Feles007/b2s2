project('glad', 'c')

inc = include_directories('include')

libglad = static_library('glad', 'src/glad.c', include_directories : inc)

glad = declare_dependency(include_directories : inc, link_with : libglad)
