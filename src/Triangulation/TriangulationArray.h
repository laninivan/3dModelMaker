#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <vector>


#ifndef TRIANGULATION_ARRAY
#define TRIANGULATION_ARRAY

class TriangulationArray {
public:
	bool isclockwiseOrCounterclockwise(int n, glm::vec2 VertexMas[]);

	bool isPointInTriangle(int n, glm::vec2 VertexMas[], glm::vec2 first, glm::vec2 second, glm::vec2 third);

	 double cross_prod(glm::vec2 first, glm::vec2  second, glm::vec2  third);

	  std::vector<glm::vec2>  triangulate(int n, glm::vec2 VertexMas[]);


};


#endif 