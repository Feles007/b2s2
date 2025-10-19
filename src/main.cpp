#include <glad/glad.h>

#include "common.hpp"
#include <GLFW/glfw3.h>

void error_callback(int error_code, const char *description) {
	// What if glfwTerminate has an error?
	static bool has_been_called = false;
	if (!has_been_called) {
		glfwTerminate();
		has_been_called = true;
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

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(.2f, .3f, .3f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
