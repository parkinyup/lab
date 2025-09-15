#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>

const double DEGREES_TO_RADIANS = glm::pi<float>() / 180.0;
const double RADIANS_TO_DEGREES = 180.0 / glm::pi<float>();


int main()
{
	glm::vec3 v(2, -1, 1);
	glm::vec3 u(1, 1, 2);

	float d = glm::dot(v, u);
	float c = d / (glm::length(u) * glm::length(v));
	float deg = glm::acos(c) * RADIANS_TO_DEGREES;

	std::cout << deg << std::endl;
	return 0;
}

