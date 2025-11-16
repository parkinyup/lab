
//#define GLFW_INCLUDE_GLU

#include <iostream>


//이 순서가 바뀌면 안됨
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "MyGlWindow.h"

int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
	{
		// Initialization failed
		std::cout << "Error" << std::endl;
		return 0;
	}
	//오픈gl 버전 지정 : 별 상관은 없음 : 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//오픈gl 예전 기능은 다 빼고, 신기능만 쓰는 것(예전 기능 사용하려면 : compatible_profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 800;
	int height = 800;
	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL FrameWork", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (gl3wInit()) {
		fprintf(stderr, "failed to initialize OpenGL\n");
		return -1;
	}
	if (!gl3wIsSupported(3, 2)) {
		fprintf(stderr, "OpenGL 3.2 not supported\n");
		return -1;
	}
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
	glGetString(GL_SHADING_LANGUAGE_VERSION));
	glfwSwapInterval(1); //enable vsync

	printf("OpenGL %s, GLSL %s\n",
	glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	while (!glfwWindowShouldClose(window))
	{



		//////////////////////////////
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
		/* Swap front and back buffers */
		
		/* Poll for and process events */
		
		glfwDestroyWindow(window);
		glfwTerminate();
		return 0;
}


