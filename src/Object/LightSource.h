#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#ifndef LIGHT_S
#define LIGHT_S

class LightSourse {
public:
	LightSourse();
	LightSourse(glm::vec3 position, glm::vec3 color);
	glm::vec3 getColor();
	glm::vec3 getPos();

private:
	glm::vec3 color;
	glm::vec3 position;

};
#endif