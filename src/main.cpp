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

int main() {
	glfwSetErrorCallback(error_callback);

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Here's some text", nullptr, nullptr);
	xassert(window);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		FATAL_ERROR("Failed to initialized GLAD");
	}
}
