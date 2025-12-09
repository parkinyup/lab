#include <glm/glm.hpp>

#ifndef __COW
#define __COW
#include "GL/gl3w.h"
#include <glm/mat4x4.hpp>
#include <vector>
class cow
{
public:
	cow();
	void setup();
	void draw();
	void calculateNormal(); //normal계산 함수
	GLuint vaoHandle;
	GLuint vbo_cow_vertices, ibo_cow_elements;
	GLuint vbo_cow_normals;
	std::vector<glm::vec3> normals; //normal저장하기 위한 곳
};

extern uint32_t nvertices[9468];
extern uint32_t stindices[9468];
extern glm::vec3 vertices[1732];
extern glm::vec2 st[3056];


#endif
