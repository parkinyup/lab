
#define GLM_ENABLE_EXPERIMENTAL 
#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

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


	//load shaders : vertex shader랑 fragment shader 지정
	shaderProgram->initFromFiles("shaders/simple.vert", "shaders/simple.frag");

	GLfloat cube_vertices[] = {
		// front 
		-1.0, -1.0, 1.0,
		1.0,-1.0, 1.0,
		1.0, 1.0, 1.0,
	   -1.0, 1.0, 1.0,
	   -1.0, -1.0,-1.0,
		1.0,-1.0,-1.0,
		1.0, 1.0,-1.0,
	   -1.0, 1.0,-1.0,
	};
	GLfloat cube_colors[] = {
		// front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};

	GLushort cube_elements[] = {
	0, 1, 2, 2, 3, 0, 1, 5, 6,
	6, 2, 1, 7, 6, 5, 5, 4, 7,
	4, 0, 3, 3, 7, 4, 4, 5, 1,
	1, 0, 4, 3, 2, 6, 6, 7, 3,
	};

	/*
	//NON-DSA(Direct State Access) 방법
	//삼각형의 정보 배열에 저장

	//삼각형 위치 저장 : 0
	const float vertexPosition[] = {
	 -0.2f, -0.2f, 0.0f, 1.0f,
	0.0f,  0.2f, 0.0f, 1.0f,
	 0.2f, -0.2f, 0.0f, 1.0f,

	};
	//삼각형 색상 지정 : 1
	const float vertexColor[] = {
	   1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,

	};

	const float vertices[] = { //interleave 방식
	   -0.2f, 0.0f, 0.0f, 1.0f,    1.0f,0.0f,0.0f, //position, color for v0
		0.0f, 0.4f, 0.0f, 1.0f,    0.0f,1.0f,0.0f,//position, color for v0
		0.2f, 0.0f, 0.0f, 1.0f,    0.0f,0.0f,1.0f
	};
	*/


	//이제 삼각형에 대한 정보를 CPU가 아닌 GPU에 보냄
	// 삼각형이 가진 색상 정보 : 위치, 색상
	// 
	//VAO 생성(vertex array object) 
	//큐브생성
	/*
	glGenVertexArrays(1, &vaohandle);
	glBindVertexArray(vaohandle);  // 이 VAO에 설정 묶기

	// ===== 3. VBO (position) =====
	GLuint vbo_position;
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,              // layout(location = 0) : position
		3,              // x,y,z  → 3개
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexAttribArray(0);

	// ===== 4. VBO (color) =====
	GLuint vbo_color;
	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,              // layout(location = 1) : color
		3,              // r,g,b
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexAttribArray(1);

	// ===== 5. IBO / EBO (index buffer) =====
	GLuint ibo_cube;
	glGenBuffers(1, &ibo_cube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
	//  GL_ELEMENT_ARRAY_BUFFER는 VAO에 묶이니까 unbind 하지 말고 그대로 둠

	// 원하는 경우만 언바인드
	glBindVertexArray(0);


}*/




/*glGenVertexArrays(1, &vaohandle); //컨테이너 생성
	glBindVertexArray(vaohandle); //바인드 : 여러개의 vao중에 (만일 여러개 있다면 어떤거 사용할래?
	//바인드 : active의미 , 난 앞으로 여기에 뭔가 자겁을 할래라고 지정, 선언

	//vbo생성ㅇ (Vertex Buffer object) : vertex의 속성 정보 제공
	GLuint vbo_position;
	glGenBuffers(1, &vbo_position);//ㅇvertex 위치 정보를 저장하기 위한 vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position); //vbo바인딩 : activate

	//데이터를 통한 메모리 -> GPU메모리를 보낸 후 할당 : 마지막 : usage
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), &vertexPosition, GL_STATIC_DRAW);
	glVertexAttribPointer(//GPU상태, 메모리에 올라온 데이터 해석 방법을 알려줌
		0, //속성 번호
		4, //데이터 수 (vertex 당)
		GL_FLOAT, //데이터 타입
		GL_FALSE, //normalize 여부
		0, //sttride
		0 //offset

	);
	//속성 enable
	glEnableVertexAttribArray(0); //속성번호 0번 enable

	GLuint vbo_color;
	glGenBuffers(1, &vbo_color);//ㅇvertex 색상 정보를 저장하기 위한 vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color); //vbo바인딩 : activate

	//데이터를 통한 메모리 -> GPU메모리를 보낸 후 할당 : 마지막 : usage
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), &vertexColor, GL_STATIC_DRAW);
	glVertexAttribPointer(//GPU상태, 메모리에 올라온 데이터 해석 방법을 알려줌
		1, //색상 번호
		3, //데이터 수 (vertex 당)
		GL_FLOAT, //데이터 타입
		GL_FALSE, //normalize 여부
		0, //sttride
		0 //offset

	);
	glEnableVertexAttribArray(1);//속성번호 1번 enable

	//IBO 생성

	//vao Bound
	glBindVertexArray(0); //현재 사용중인 vao bound(0을 넣으면 됨)*/


	/*


	//1.vao
	glGenVertexArrays(1, &vaohandle); //컨테이너 생성
	glBindVertexArray(vaohandle); //binding
		GLuint vbo_vertex;
		glGenBuffers(1, &vbo_vertex);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex); //vbo binding -> activate
		//copy data from CPU to GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
		//GPU에서 해석방법 알려줘야 함

		//위치 처리
		glVertexAttribPointer(
			0,  // 속성(attribute) 번호 : 0
			4, //vertex당 데이터 수
			GL_FLOAT,
			GL_FALSE,
			sizeof(float)*7,//위치가 시작한 후에 얼마 데이터 후에 다시 위치가 시작하나 : stride(보폭)
			(void*)0  //offset : 얼마 후에 데이터가 시작하나 ?
		);
		glEnableVertexAttribArray(0);

		//색상처리
		glVertexAttribPointer(
			1,  // 속성(attribute) 번호 : 0
			3, //vertex당 데이터 수
			GL_FLOAT,
			GL_FALSE,
			sizeof(float) * 7 ,//컬러가 시작한 후에 얼마 데이터 후에 다시 컬러가 시작하나 : stride(보폭)
			(void*)(sizeof(float)*4)  //offset : 얼마 후에 데이터가 시작하나 ?
		);
		glEnableVertexAttribArray(1);
	glBindVertexArray(0); //unbinding
	*/


	//DSA 방법 : 함수 명이 다름 (glBinding이 없음)
	 //1. vao 생성
	GLuint vbo_position;
	GLuint vbo_color;
	GLuint ibo_cube;
	//glCreate로 시작 -> DSA 방법
	glCreateVertexArrays(1, &vaohandle);
	glCreateBuffers(1, &vbo_position);
	glCreateBuffers(1, &vbo_color);
	glCreateBuffers(1, &ibo_cube);

	//  position 
	glNamedBufferData(vbo_position, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vaohandle, 0, vbo_position, 0, sizeof(float) * 3);

	glVertexArrayAttribFormat(vaohandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaohandle, 0, 0);
	glEnableVertexArrayAttrib(vaohandle, 0);

	// color 
	glNamedBufferData(vbo_color, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vaohandle, 1, vbo_color, 0, sizeof(float) * 3);

	glVertexArrayAttribFormat(vaohandle, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaohandle, 1, 1);
	glEnableVertexArrayAttrib(vaohandle, 1);

	// IBO 
	glNamedBufferData(ibo_cube, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
	glVertexArrayElementBuffer(vaohandle, ibo_cube);
}

		


	/*
	//DSA 방법 : 함수 명이 다름 (glBinding이 없음)
	 //1. vao 생성
	GLuint vbo_position;
	GLuint vbo_color;
	//glCreate로 시작 -> DSA 방법
	glCreateVertexArrays(1, &vaohandle);
	glCreateBuffers(1, &vbo_position);
	glCreateBuffers(1, &vbo_color);


	//2. vbo 생성
	//position 처리
	//GPU 메모리 할당
	glNamedBufferData(vbo_position, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
	//GPU에게 해석방법 알려줌
	glVertexArrayVertexBuffer(
		vaohandle, //vao
		0,//binding index 번호
		vbo_position, //vbo
		0,//offset 
		sizeof(float)*4 //stride
	);

	//color 처리
	//GPU 메모리 할당
	glNamedBufferData(vbo_color, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);
	//GPU에게 해석방법 알려줌
	glVertexArrayVertexBuffer(
		vaohandle, //vao
		1,//binding index 번호
		vbo_color, //vbo
		0,//offset 
		sizeof(float) * 3 //stride
	);

	glVertexArrayAttribFormat(vaohandle,
		0, //속성(attribute) 번호 
		4, //vertex당 데이터 수
		GL_FLOAT,
		GL_FALSE,
		0 // offset
	);

	glVertexArrayAttribBinding(vaohandle,
		0, //속성번호 0
		0  //binding index 0
	);

	glEnableVertexArrayAttrib(vaohandle, 0); //0번 속성 enable

	glVertexArrayAttribFormat(vaohandle,
		1, //속성(attribute) 번호 
		3, //vertex당 데이터 수
		GL_FLOAT,
		GL_FALSE,
		0 // offset
	);

	glVertexArrayAttribBinding(vaohandle,
			1, //속성번호 0
			1  //binding index 0
	);

	glEnableVertexArrayAttrib(vaohandle, 1); //0번 속성 enable
*/

		//DSA - Interleave 방식
/*
		GLuint vbo_vertex;
		glCreateVertexArrays(1, &vaohandle);
		glCreateBuffers(1, &vbo_vertex);

		glNamedBufferData(vbo_vertex, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vaohandle, 0, vbo_vertex, 0, sizeof(float) * 7);


		//시험 나옴*********************
		glVertexArrayAttribFormat(vaohandle, 0, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vaohandle, 0, 0); //0 : 속성 번호 0 : binding index
		glEnableVertexArrayAttrib(vaohandle, 0); //속성번호 0 enable

		glVertexArrayAttribFormat(vaohandle, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*4);
		glVertexArrayAttribBinding(vaohandle, 1, 0); //1 : 속성 번호 0 : binding index
		glEnableVertexArrayAttrib(vaohandle, 1); //속성번호 1 enable
		}
		*/
		
		


		void MyGlWindow::draw(void)
	 {
	
	glClearColor(0.2, 0.2, 0.2, 1); //백그라운드 색상 지정(R,G,B,A)
	//어떤 버퍼를 지울지 지정 : 라스터라이제이션 할때 두개의 버퍼:color,depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//0. 뷰포트설정 : 캔버스 크기 및 위치 설정 : 현재는 800x800인데 이걸 다 쓸건지 일부만 쓸건지 결정
	glViewport(0, 0, m_width, m_height); //앞 두개는 시작점 뒤 두개는 크기
	
	//1. 쉐이더 use
	shaderProgram->use();
	//인덱스가 있을때 그리기
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	//2. vao binding
	glBindVertexArray(vaohandle);
	//3.call draw function
	// 
	// 인덱스가 없을 때 그리기
	//glDrawArrays(GL_TRIANGLES, 0, 4); //어떻게 그릴래? 삼각형으로, 시작 인덱스, 버텍스 수   GL_TRIANGLES는 3개씩 끊어서, STRIP은 자동으로 반복시켜줌
	//4.쉐이더 disable
	shaderProgram->disable();


	}
		
