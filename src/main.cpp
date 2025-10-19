#include <glad/glad.h>

#include "common.hpp"
#include "file_reader.hpp"
#include <GLFW/glfw3.h>

void error_callback(int error_code, const char *description) {
	// What if glfwTerminate has an error?
	static bool has_been_called = false;
	if (!has_been_called) {
		glfwTerminate();
		has_been_called = true;
		std::puts("glfwTerminate had an error");
	}
	FATAL_ERROR("OpenGL Error %d - %s", error_code, description);
}

void framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {

	const int width  = 800;
	const int height = 600;

	glfwSetErrorCallback(error_callback);

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(width, height, "Here's some text", nullptr, nullptr);
	xassert(window);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		FATAL_ERROR("Failed to initialized GLAD");
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float vertices[] = {-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0};

	unsigned vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const auto vertex_shader_src = FileData::read_file("src/shaders/vertex.glsl");
	FileData::deallocate(vertex_shader_src);

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(.2f, .3f, .3f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
