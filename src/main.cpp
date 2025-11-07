#include <glad/glad.h>

#include "common.hpp"
#include "shader.hpp"
#include "shader_gen.hpp"
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

	//
	// SETUP
	//

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

	//
	// Buffers
	//

	float vertices[] = {-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0};

	u32 vbo, vao;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	//
	// Shaders
	//

	const auto shader_program = ShaderProgram::create(shader::vertex_src, shader::fragment_src);

	//
	// Main loop
	//

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(.2f, .3f, .3f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		shader_program.use();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
