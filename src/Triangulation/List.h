#ifndef LIST_H
#define LIST_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace std;

class Node { 
public:
	int index;
    double x, y;
	Node *prev, *next;
	Node (double a = 0.0, double b = 0.0): x(a), y(b), prev(0), next(0) {}
};


typedef enum { clockwise, count_clockwise, error } type;

class List {
public:
	int size;
	Node* cur; 
	List (int s = 0, Node* tmp = 0): size(s), cur(tmp) {}
	bool is_empty () {
	  return ( size == 0 ? true : false );
	}
	void insert (double a, double b);
	void insert (vector<glm::vec2>a); 
	Node* find (double a, double b); 
	Node* findMinX();
	Node* findMaxX();
	void delete_node (double a, double b); 
	double cross_prod (Node *first, Node *second, Node *third);
	type direction ();
	
	bool is_in_triangle (Node *first, Node *second, Node *third);
	bool isTriangleDegenerate(glm::vec2 A, glm::vec2 B, glm::vec2 C);
	vector <int> triangulation (); 
	vector<int> List::triangulationMomoton();
};

#endif 
