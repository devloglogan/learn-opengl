#include <fstream>
#include <iostream>
#include <string>

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

// clang-format off
GLfloat vertices[] = {
	 0.0f,  0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
};
// clang-format on

std::string read_file(const char *path) {
	std::ifstream f(path);
	if (!f.is_open()) {
		std::cerr << "Failed to open file: " << path << "\n";
		return "";
	}
	return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

void process_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	const float TARGET_ASPECT_RATIO = 640.0f / 480.0f;
	int viewport_width, viewport_height, viewport_x, viewport_y;

	float window_aspect = (float)width / (float)height;

	if (window_aspect > TARGET_ASPECT_RATIO) {
		viewport_height = height;
		viewport_width = (int)(height * TARGET_ASPECT_RATIO);
		viewport_x = (width - viewport_width) / 2;
		viewport_y = 0;
	} else {
		viewport_width = width;
		viewport_height = (int)(width / TARGET_ASPECT_RATIO);
		viewport_x = 0;
		viewport_y = (height - viewport_height) / 2;
	}

	glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
}

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(640, 480, "Learn OpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Could not create GLFW window\n";
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return 1;
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);

	std::string vertex_src = read_file("res/shaders/default.vert.glsl");
	std::string fragment_src = read_file("res/shaders/default.frag.glsl");

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *vertex_src_ptr = vertex_src.c_str();
	glShaderSource(vertex_shader, 1, &vertex_src_ptr, nullptr);
	glCompileShader(vertex_shader);
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << "\n";
	}

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragment_src_ptr = fragment_src.c_str();
	glShaderSource(fragment_shader, 1, &fragment_src_ptr, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << "\n";
	}

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << "\n";
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
