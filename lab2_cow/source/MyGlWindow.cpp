
#define GLM_ENABLE_EXPERIMENTAL 
#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "cow.h"

MyGlWindow::MyGlWindow(int w, int h)

//==========================================================================
{
	m_width = w;
	m_height = h;

	setupBuffer();
	
}




void MyGlWindow::setupBuffer()
{

	//쉐이더 객체 생성 : modern c++
	shaderProgram = std::make_unique<ShaderProgram>();

	shaderProgram->initFromFiles("shaders/simple.vert", "shaders/simple.frag");

	shaderProgram->addUniform("model");
	shaderProgram->addUniform("view");
	shaderProgram->addUniform("projection");

	m_cow = std::make_unique<cow>();

	float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);

	m_viewer = std::make_unique<Viewer>(
		glm::vec3(3.0f, 3.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		45.0f,
		aspect

	);
	
glEnable(GL_DEPTH_TEST);       // 깊이 테스트 켜기
glDepthFunc(GL_LESS);
}

		

		void MyGlWindow::draw(void)
	 {
	
	glClearColor(0.2, 0.2, 0.2, 1); //백그라운드 색상 지정(R,G,B,A)
	//어떤 버퍼를 지울지 지정 : 라스터라이제이션 할때 두개의 버퍼:color,depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//0. 뷰포트설정 : 캔버스 크기 및 위치 설정 : 현재는 800x800인데 이걸 다 쓸건지 일부만 쓸건지 결정
	glViewport(0, 0, m_width, m_height); //앞 두개는 시작점 뒤 두개는 크기

	glm::mat4 translate = glm::translate(glm::mat4(1.0f),
		glm::vec3(0.3f, 0.0f, 0.0f));   // x로 0.3 이동
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f),
		glm::radians(45.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));        // y축 45도 회전
	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f));          // 크기 유지

	glm::mat4 model = translate * rotate * scale;

	glm::vec3 eye = m_viewer->getViewPoint();
	glm::vec3 center = m_viewer->getViewCenter();
	glm::vec3 up = m_viewer->getUpVector();

	glm::mat4 view = glm::lookAt(eye, center, up);

	float fovy = glm::radians(m_viewer->getFieldOfView());  // Viewer 안 값은 degree 기준
	float aspect = m_viewer->getAspectRatio();
	float zNear = 0.1f;
	float zFar = 100.0f;

	glm::mat4 projection = glm::perspective(fovy, aspect, zNear, zFar);
	
	//1. 쉐이더 use
	shaderProgram->use();
	//인덱스가 있을때 그리기
	/*int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	//2. vao binding
	glBindVertexArray(vaohandle);
	//3.call draw function
	// 
	// 인덱스가 없을 때 그리기
	//glDrawArrays(GL_TRIANGLES, 0, 4); //어떻게 그릴래? 삼각형으로, 시작 인덱스, 버텍스 수   GL_TRIANGLES는 3개씩 끊어서, STRIP은 자동으로 반복시켜줌
	//4.쉐이더 disable*/

	glm::mat4 mvp = projection * view * model;

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->uniform("model"),
		1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(shaderProgram->uniform("view"),
		1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(shaderProgram->uniform("projection"),
		1, GL_FALSE, glm::value_ptr(projection));

	// ★ 4. VAO 바인딩을 먼저 하고 → 그 다음에 glGetBufferParameteriv / glDrawElements
	/*glBindVertexArray(vaohandle);

	int size = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);*/

	if (m_cow)
		m_cow->draw();

	shaderProgram->disable();


	}
		
