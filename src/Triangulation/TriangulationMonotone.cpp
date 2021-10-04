#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "List.h"

#ifndef TRIANGULATION_MONOTONE
#define TRIANGULATION_MONOTONE

class TriangulationMonotone {
public:
	

	//bool isTriangleDegenerate(glm::vec2 A, glm::vec2 B, glm::vec2 C)
	//{

	//	float AB = glm::length(A - B);
	//	float AC = glm::length(A - C);
	//	float BC = glm::length(B - C);
	//	return(AB + AC <= BC || BC + AB <= AC || BC + AC <= AB);
	//}


	// vector<glm::vec2> triangulation(List* polygon)
	//{
	//	 vector<glm::vec2> triangles;
	//	 Node* BEGIN = polygon->findMinX();
	//	 Node* UP = BEGIN;//next
	//	 Node* DO = BEGIN;//prev
	//	 Node* END = polygon->findMaxX();
	//	 while (UP != END && DO != END)
	//	 {
	//		 if (UP->next->x < DO->prev->x && UP != END)
	//		 {

	//			 if (!isTriangleDegenerate(glm::vec2(UP->x, UP->y), glm::vec2(UP->next->x, UP->next->y), glm::vec2(DO->x, DO->y)))
	//			 {
	//				 triangles.push_back(glm::vec2(UP->x, UP->y));
	//				 triangles.push_back(glm::vec2(UP->next->x, UP->next->y));
	//				 triangles.push_back(glm::vec2(DO->x, DO->y));
	//			 }
	//			 UP = UP->next;
	//		 }
	//		 else  if (DO != END)
	//		 {

	//			 if (!isTriangleDegenerate(glm::vec2(UP->x, UP->y), glm::vec2(DO->prev->x, DO->prev->y), glm::vec2(DO->x, DO->y)))
	//			 {
	//				 triangles.push_back(glm::vec2(UP->x, UP->y));
	//				 triangles.push_back(glm::vec2(DO->prev->x, DO->prev->y));
	//				 triangles.push_back(glm::vec2(DO->x, DO->y));
	//			 }
	//			 DO = DO->prev;
	//		 }

	//	 }
	//	 return triangles;

	//}

};
#endif 