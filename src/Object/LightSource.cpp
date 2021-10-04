#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#ifndef LIGHT_S
#define LIGHT_S

class LightSourse {
public:
	LightSourse()
	{
		this->position = glm::vec3(20.0f, 40.0f, 60.0f);
		this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	}
	LightSourse(glm::vec3 position, glm::vec3 color)
	{
		this->position = position;
		this->color = color;
	}
	glm::vec3 getColor()
	{
		return this->color;
	}
	glm::vec3 getPos()
	{
		return this->position;
	}

private:
	glm::vec3 color;
	glm::vec3 position;
};
#endif