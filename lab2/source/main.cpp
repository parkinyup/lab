#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x2.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

const double DEGREES_TO_RADIANS = glm::pi<float>() / 180.0;
const double RADIANS_TO_DEGREES = 180.0 / glm::pi<float>();

//normal vector 구하기
/*int main()
{
	glm::vec3 p1(3, 0, 0);
	glm::vec3 p2(1.5, 0.86, 0);
	glm::vec3 p3(3, 0, -1);

	glm::vec3 v1 = p2 - p1;
	glm::vec3 v2 = p3 - p1;

    glm::vec3 v3 = glm::normalize(glm::cross(v1, v2));

    std::cout << glm::to_string(v3) << std::endl;
    
    return 0;
}
int main() {
	glm::vec4 v1 = { 1,0,1,-1 };
	glm::vec4 v2 = { 1,0,1,-1 };
	glm::vec4 v3 = { 1,0,1,-1 };
	glm::vec4 v4 = { 1,0,1,-1 };

	glm::mat4 m; //glm:mat3 -> 3x3
	m[0] = v1;
	m[1] = v2;
	m[2] = v3;
	m[3] = v4;

	std::cout << glm::to_string(m) << std::endl;
	return 0;
}


int main() {
	glm::mat3 A = { {1,1,-1},{0,2,0},{2,3,1} };

	glm::mat3 B = { {1,0,0},{0,-1,1},{0,1,2 } };

	glm::mat3 AB = A * B;

	glm::mat3 BA = B * A;

	std::cout << glm::to_string(AB) << std::endl;

	std::cout << glm::to_string(BA) << std::endl;

	return 0;

	
}

int main() {
	glm::mat2 m2 = { 1, 0, 1, -1 };
	glm::mat2 im = glm::inverse(m2);
	std::cout << to_string(im) << std::endl;

	glm::mat2 ii = m2 * im;
	std::cout << to_string(ii) << std::endl;
}

int main() {
	glm::mat3 M = glm::mat3{ {1,0,0},{2,-1,0},{3,0,1} };
	glm::vec3 A(1, 2, 3);
	

	std::cout << glm::to_string(M * A) << glm::to_string(A * M) << std::endl;
}

int main()
{
	glm::vec3 v(5, 6, 1);
	glm::mat3 t(1.0); //identity matrix
	t = glm::translate(t, glm::vec2(2, 3));
	v = t * v;
	std::cout << to_string(t) << std::endl;
	std::cout << to_string(v) << std::endl;
	return 0;
}

int main()
{
	glm::vec3 v(5, 6, 1);
	glm::mat3 t(1.0);
	t = glm::scale(t, glm::vec2(3, 4)); //scale 3x in x axis and 4x in y axis
	v = t * v;
	std::cout << to_string(t) << std::endl;
	std::cout << to_string(v) << std::endl;
	return 0;
}

int main()
{
	glm::vec3 v(5, 6, 1);
	glm::mat3 t(1.0);
	t = glm::rotate(t, glm::radians(45.0f)); //45 or 45.0 causes an error
	
		v = t * v;
	std::cout << to_string(t) << std::endl;
	std::cout << to_string(v) << std::endl;
	return 0;
}

int main()

{
	glm::vec3 campos(5, 5, 5);
	glm::vec3 look(0, 0, 0);
	glm::vec3 up(0, 1, 0);
	std::cout << glm::to_string(lookAt(campos, look, up)) << std::endl;
	return 0;

}

glm::mat4 lookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up)

{
	glm::vec3 z = glm::normalize(campos - look);
	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec3 y = glm::normalize(glm::cross(z, x));

	glm::mat4 Trans = glm::translate(glm::mat4(1), -campos);
	glm::mat4 rot({ x.x,y.x,z.x,0 }, { x.y,y.y,z.y,0 }, { x.z,y.z,z.z,0 }, { 0,0,0,1 });

	return rot * Trans;

}

int main()
{
	glm::mat3 t(1.0);
	//this equals to scale*(rotate*(t * translate))
	t = glm::translate(t, glm::vec2(3, 4));
	t = glm::rotate(t, -45.0f);
	t = glm::scale(t, glm::vec2(2, 2));
	std::cout << to_string(t) << std::endl;

	glm::mat3 o(1.0);
	glm::mat3 s = glm::scale(o, glm::vec2(2, 2));
	glm::mat3 r = glm::rotate(o, -45.0f);
	glm::mat3 tr = glm::translate(o, glm::vec2(3, 4));
	glm::mat3 composite = tr * r * s;
	std::cout << to_string(composite) << std::endl;
	return 0;
}

int main() {
	
	glm::vec4 v(4.0f, 5.0f, 3.0f, 1.0f);

	
	glm::mat4 M(1.0f);
	M = glm::translate(M, glm::vec3(0.0f, 5.0f, 0.0f));          // Y translation = 5
	M = glm::rotate(M, glm::radians(40.0f), glm::vec3(1, 0, 0)); // X rotation
	M = glm::rotate(M, glm::radians(56.0f), glm::vec3(0, 1, 0)); // Y rotation
	M = glm::scale(M, glm::vec3(1.3f));                          // uniform scale = 1.3

	glm::vec4 wp = M * v;

	std::cout <<  glm::to_string(wp) << std::endl;
}

int main()

{

	glm::vec4 v(4.0f, 5.0f, 3.0f, 1.0f);

	glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(1.3f, 1.3f, 1.3f));
	glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, 0.0f));
	
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(40.0f), glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, glm::radians(56.0f), glm::vec3(0, 1, 0));
	rotate = glm::rotate(rotate, glm::radians(0.0f), glm::vec3(0, 0, 1));
	
	//SRT
	glm::mat4 m = t * rotate * s;
	glm::vec4 wp = m * v;

	std::cout << glm::to_string(wp) << std::endl;

	glm::mat4 view = { {0.84f, -0.28f, 0.46f, 0}, 
							{0, 0.86f,0.52f,0} ,
							{-0.54f,-0.43f, 0.72f,0},
								{0,0,-49.28f,1.0f} };
	//위에 view로 부터, 카메라 위치랑 카메라가 보고 있는 점을 어떻게 알지?
	//view행렬은 world -> camera 변경하는 행렬
	//inverse(view)는 camera -> world 행렬이 됨

	glm::mat4 inView = glm::inverse(view); //camera - >world
	//inView의 마지막 칼럼이 카메라 위치가 됨
	

	glm::vec3 camPos = inView[3]; //카메라 위치
	//view 구성시, 3개의 축을 구했는데, 카메라는 -z 방향을 바라본다고 가정
	//카메라는 -z축을 바라보고 있으므로 
	glm::vec3 z_axis = glm::normalize(-inView[2]);

	glm::vec3 look = camPos + z_axis * 10.0f;
	glm::vec3 up(0, 1, 0);
	glm::mat4 myView = lookAt(camPos, look, up);

	std::cout << glm::to_string(myView) << std::endl;


	return 0;

}*/

glm::mat4 perspective(float fovy, float aspect, float near, float far)

{

	glm::mat4 projection_matrix(0.0f);

	projection_matrix[0][0] = 1.0f / (aspect * tan(glm::radians(fovy) / 2.0f));
	projection_matrix[1][1] = 1.0f / tan(glm::radians(fovy) / 2.0f);
	projection_matrix[2][2] = -((far + near) / (far - near));
	projection_matrix[2][3] = -1.0f;
	projection_matrix[3][2] = -(2.0f * far * near / (far - near));

	return projection_matrix;

}

int main()

{
	float width = 780.0f;
	float height = 750.0f;
	float fovY = 45.0f;
	float nearz = 0.1f;
	float farz = 500.0f;

	float aspect = width / height;

	glm::mat4 pm = perspective(fovY, aspect, nearz, farz);

	std::cout << glm::to_string(pm) << std::endl;
	return 0;

}