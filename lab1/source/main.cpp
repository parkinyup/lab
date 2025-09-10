#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

//glm은 객체지향이 아니다. c와 비슷하다

int main()
{

	//Q1 Point p(1,4,-5)를 vector v(5,1,4) 만큼 이동하라
	glm::vec3 p(1, 4, -5);
	glm::vec3 v(5, 1, 4);

	p = p + v;

	std::cout << glm::to_string(p) << std::endl;

	//Q2 vector v1(1, 0, 0) 와 vector v2(0, 1, 0)들 
	glm::vec3 v1(1, 0, 0);
	glm::vec3 v2(0, 1, 0);

	v1 = v1 + v2;

	std::cout << glm::to_string(v1) << std::endl;


	//Q3. Vector v1(0, 1, 0) 의 길이를 두 배 만큼 키우시오
	glm::vec3 v4(0.0f, 1.0f, 0.0f);

	v4 = v4 * 2.0f;

	std::cout << glm::to_string(v4) << std::endl;

	//Q4. 시작점(8, 2, 5) 과 끝점(1, -1, 4)를 잇는 벡터를 구하시오
	glm::vec3 v5(8, 2, 5);
	glm::vec3 v6(1, -1, 4);

	v5 = v6 - v5;

	std::cout << glm::to_string(v5) << std::endl;
	
	//Q5. vector v(1, 3, 4)를 정규화(normalize)하시오
	glm::vec3 v7 = glm::vec3(1, 3, 4);
	
	glm::vec3 v8 = glm::normalize(v7); 

	std::cout << glm::to_string(v8) << std::endl;
	
	//Q6. 3차원 vector v(1, -1, 4)를 4차원벡터로 변환하고 w값을 0으로 설정하시오.
	glm::vec3 v9(1, -1, 4);
	glm::vec4 v10(v9, 0.0);

	std::cout << glm::to_string(v10) << std::endl;

	//벡터의 길이를 구함

	glm::vec3 b(1.0f, 4.0f, 2.0f);

	b = b * 3.0f;  //스칼라 곱 : 타입 맞추어야 함

	b = 3.0f * b;

	glm::vec3 c = glm::vec3(1, 1, 1);
	//길이가 1인 정규벡터로 바꾸기

	glm::vec3 d = glm::normalize(c); //주의 : 틀리는 사람 많음

	c.xyz = d.xyz;



	return 0;
}

