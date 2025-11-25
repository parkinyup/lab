
//#define GLFW_INCLUDE_GLU

#include <iostream>


//이 순서가 바뀌면 안됨
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "MyGlWindow.h"
#include <memory>
std::unique_ptr<MyGlWindow> win; //modern c++ : shared_ptr
//MyGlWindow * win;  


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
	//윈도우 제대로 생성

	//opengl 컨텍스트 생성-> 컨텍스트? 구조체(struct) 생성

	//opengl 구조체 생성
	glfwMakeContextCurrent(window);

	//헬퍼초기화 : opengl의 함수를 이용하기 위해 helper(loader)를 초기화
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

	//모니터의 refresh rate sync.
	glfwSwapInterval(1); //enable vsync 1을 넣으면 sync를 맞춰주는거


	//MyglWindow 객체 생성
	//win = new MyGlWindow(width, height);
	//modern C++ 이름 : 스마트 포인터(필수로 익혀둘것)
	win = std::make_unique <MyGlWindow>(width,height);
	
	
	//printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	while (!glfwWindowShouldClose(window))
	{
		//여기에 뭔가를 그려줘야 함
		


		//매프레임 draw()함수 호출
		win->draw();


		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();

	}
		/* Swap front and back buffers */
		
		glfwDestroyWindow(window);
		glfwTerminate();

		return 0;
}


