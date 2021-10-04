#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "List.h"
#include "TriangulationArray.cpp"


#ifndef TRIANGULATION
#define TRIANGULATION

class Triangulation {
public:
	static vector<int> earClippingList(List* polygon) {
		return polygon->triangulation();
	}
	static vector<glm::vec2> earClippingArray(TriangulationArray triang,int n, glm::vec2 mas[])
	{	
		return triang.triangulate(n,mas);
	}
	 static vector<int> triangulationMonotone(List* polygon)
	{

		 return polygon->triangulationMomoton();
	}
};


#endif 