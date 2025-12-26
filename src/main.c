#include <stdio.h>

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"

// clang-format off
GLfloat vertices[] = {
	 0.0f,  0.0f,
	 0.25f,  0.0f,
};
// clang-format on

const GLchar vertex_src[] = {
#embed "../res/shaders/default.vert.glsl"
	, '\0'
};

const GLchar fragment_src[] = {
#embed "../res/shaders/default.frag.glsl"
	, '\0'
};

void process_input(GLFWwindow *p_window, float p_delta_time, float *r_angle) {
	if (glfwGetKey(p_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(p_window, true);
	}

	const float ROTATION_SPEED = glm_rad(180.0f);
	if (glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS) {
		*r_angle += p_delta_time * ROTATION_SPEED;
	}
	if (glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS) {
		*r_angle -= p_delta_time * ROTATION_SPEED;
	}
}

void framebuffer_size_callback(GLFWwindow *p_window, int p_width, int p_height) {
	const float TARGET_ASPECT_RATIO = 1.0f;
	int viewport_width, viewport_height, viewport_x, viewport_y;

	float window_aspect = (float)p_width / (float)p_height;

	if (window_aspect > TARGET_ASPECT_RATIO) {
		viewport_height = p_height;
		viewport_width = (int)(p_height * TARGET_ASPECT_RATIO);
		viewport_x = (p_width - viewport_width) / 2;
		viewport_y = 0;
	} else {
		viewport_width = p_width;
		viewport_height = (int)(p_width / TARGET_ASPECT_RATIO);
		viewport_x = 0;
		viewport_y = (p_height - viewport_height) / 2;
	}

	glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
}

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(640, 480, "Learn OpenGL", nullptr, nullptr);
	if (window == nullptr) {
		fprintf(stderr, "Could not create GLFW window\n");
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		return 1;
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const GLchar *const[]){ vertex_src }, nullptr);
	glCompileShader(vertex_shader);
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
		fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", info_log);
	}

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, (const GLchar *const[]){ fragment_src }, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
		fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", info_log);
	}

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
		fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	float time = 0.0f;
	float angle = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		float delta_time = glfwGetTime() - time;
		time += delta_time;
		process_input(window, delta_time, &angle);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);

		mat3 transform = GLM_MAT3_IDENTITY_INIT;
		glm_rotate2d(&transform[0], angle);
		glUniformMatrix3fv(glGetUniformLocation(shader_program, "u_transform"), 1, false, &transform[0][0]);

		glBindVertexArray(vao);
		glPointSize(10.0f);
		glDrawArrays(GL_POINTS, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
