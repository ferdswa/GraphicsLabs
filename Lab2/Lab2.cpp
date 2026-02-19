#include "shader.h"
#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "file.h"
#include "error.h"

GLfloat vertices[] =
{
	//pos				//col
	0.f,  0.5f,			1.f,0.f,0.f,
	-0.5f, -0.5f,		0.f,1.f,0.f,
	0.5f,  -0.5f,		0.f,0.f,1.f
};



#define NUM_BUFFERS 1
#define NUM_VAOS 1
GLuint Buffers[NUM_BUFFERS];
GLuint VAOs[NUM_VAOS];

float xOffset = 0.f;
float yOffset = 0.f;

void (APIENTRY* DEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "A Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);

	gl3wInit();

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback((GLDEBUGPROC)DebugCallback, 0);

	GLuint program = CompileShader("triangle.vert", "triangle.frag");

	glCreateBuffers(NUM_BUFFERS, Buffers);
	glNamedBufferStorage(Buffers[0], sizeof(vertices), vertices, 0);
	glGenVertexArrays(NUM_VAOS, VAOs);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		static const GLfloat bgd[] = { 1.f, 1.f, 1.f, 1.f };
		glClearBufferfv(GL_COLOR, 0, bgd);

		glUseProgram(program);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES,0,3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}