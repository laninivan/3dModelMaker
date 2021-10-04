#include <string>
#include "../Renderer/ShaderProgram.cpp"
#include "../Object/LightSource.cpp"
#include "../Camera/camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Renderer/Mesh.cpp"

#ifndef CUBE
#define CUBE

class Cube :public Mesh {

public:

	Cube(double radius, glm::vec3 location, glm::vec3 scale, float rotAngleX, float rotAngleY, float rotAngleZ) :
		Mesh(generVertexes(radius), generIndices(), location, scale, rotAngleX, rotAngleY, rotAngleZ) {};
	

private:
	std::vector<Vertex> generVertexes(double radius);
	std::vector<unsigned int> generIndices();
	double radius;
};






#endif
