#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "List.h"




using namespace std;

void List::insert(double a, double b) {
	Node* tmp = new Node;
	tmp->x = a; tmp->y = b;
	if (is_empty()) {
		tmp->next = tmp;
		tmp->prev = tmp;		
	}
	else {
		tmp->next = cur->next;
		cur->next = tmp;
		tmp->prev = cur;
		tmp->next->prev = tmp;
	}
	cur = tmp; 
	tmp->index = size;
	size++;
}

void List::insert(vector<glm::vec2>a) {
	Node* tail = 0;
	
	if (is_empty()) {
		for (int i = 0; i < a.size(); i ++) {
			insert(a[i].x, a[i].y);
			//ук на нач
			if (i == 0)
				tail = cur;
		}
		//замыкание
		cur->next = tail;
		cur->next->prev = cur;
		cur = cur->next;
	}
}

Node* List::find(double a, double b) {
	Node* tmp = cur;
	if (!is_empty()) {
		do {
			if (a == tmp->x && b == tmp->y)
				return tmp;
			else
				tmp = tmp->next;
		} while (tmp != cur);
	}
	return 0;
}
Node* List::findMinX()
{
	Node* tmp = cur,*min=cur;
	double min_x = tmp->x;

	if (!is_empty()) {
		do {
			if (tmp->x < min_x) {
				min_x = tmp->x;
				min = tmp;
			}
			tmp = tmp->next;
		} while (tmp != cur);	
	}
	return min;
}
Node* List::findMaxX()
{
	Node* tmp = cur, * max = cur;
	double max_x = tmp->x;
	if (!is_empty()) {
		do {
			if (tmp->x > max_x) {
				max_x = tmp->x;
				max = tmp;
			}
			tmp = tmp->next;
		} while (tmp != cur);
	}
	return max;
}

void List::delete_node(double a, double b) {
	Node* tmp = find(a, b);
	if (tmp) { //вершина с такими координатами найдена
		//если удал€етс€ текуща€ вершина, смещаем указатель на предыдущую
		if (tmp == cur)
			cur = cur->prev;
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		delete tmp;
		size--;
	}
}

double List::cross_prod(Node* first, Node* second, Node* third) {
	double x1 = second->x - first->x, x2 = third->x - first->x,
		y1 = second->y - first->y, y2 = third->y - first->y;
	return (x1 * y2 - x2 * y1);
}

type List::direction() {
	Node* tmp = cur, * min = cur;
	double min_x = tmp->x, min_y = tmp->y;

	if (!is_empty()) {
		do {
			if (tmp->x < min_x) {
				min_x = tmp->x;
				min = tmp;
			}
			if (tmp->x == min_x && tmp->y < min_y) {
				min_y = tmp->y;
				min = tmp;
			}
			tmp = tmp->next;
		} while (tmp != cur);

		return ((cross_prod(min, min->next, min->prev) < 0) ? clockwise : count_clockwise);
	}
	return error;
}

bool List::is_in_triangle(Node* first, Node* second, Node* third) {
	double a, b, c;
	Node* tmp = cur;
	do {
		if (tmp != first && tmp != second && tmp != third) {
			a = cross_prod(tmp, first, second);
			b = cross_prod(tmp, second, third);
			c = cross_prod(tmp, third, first);
			//кака€-либо из точек многоугольника попадает внутрь треугольника
			if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
				return true;
		}
		tmp = tmp->next;
	} while (tmp != cur);
	return false;
}
vector <int> List::triangulation() {
	vector <int> triangles;
	Node* first = cur, * second = cur->next, * third = cur->next->next;

	type cond = direction();
	double prod;
	if (cond != error) {
		while (size > 3) {
			prod = cross_prod(first, second, third);
		
			if ((cond == clockwise && prod < 0) || (cond == count_clockwise && prod > 0)) {
				if (!is_in_triangle(first, second, third)) {
					triangles.push_back(first->index);
					triangles.push_back(second->index);
					triangles.push_back(third->index);

					delete_node(second->x, second->y);
					second = third;
					third = third->next;
				}
				first = second;
				second = third;
				third = third->next;
			}
			else {
				first = second;
				second = third;
				third = third->next;
			}
		}
		if (size == 3) { //добавл€ем последний треугольник

			triangles.push_back(first->index);
			triangles.push_back(second->index);
			triangles.push_back(third->index);
		}
		return triangles;
	}
	return triangles;
}

bool  List::isTriangleDegenerate(glm::vec2 A, glm::vec2 B, glm::vec2 C)
{

	float AB = glm::length(A - B);
	float AC = glm::length(A - C);
	float BC = glm::length(B - C);
	return(AB + AC <= BC || BC + AB <= AC || BC + AC <= AB);
}

vector<int> List::triangulationMomoton()
{
	double prodU;
	double prodD;
	vector<int> triangles;
	Node* BEGIN = findMinX();
	Node* UP = BEGIN;//next
	Node* DO = BEGIN;//prev
	Node* END = findMaxX();
	while (UP->x != END->x && UP->y != END->y || DO->x != END->x && DO->y != END->y)
	{
		prodU = cross_prod(DO, UP, UP->next);
		prodD = cross_prod(UP, DO, DO->prev);
		if ((UP->x != END->x || UP->y != END->y) &&
					(((UP->next->x < DO->prev->x) &&((prodU > 0)|| glm::vec2(DO->x, DO->y) == glm::vec2(UP->x, UP->y))) || 
					prodD >= 0))
		{		
				if (!isTriangleDegenerate(glm::vec2(UP->x, UP->y), glm::vec2(UP->next->x, UP->next->y), glm::vec2(DO->x, DO->y)))
				{
					triangles.push_back(UP->index);
					triangles.push_back(UP->next->index);
					triangles.push_back(DO->index);
					
				}
				UP = UP->next;
	
		}
		else  if ((DO->x != END->x|| DO->y != END->y)&&
						((((prodD < 0 ))|| glm::vec2(DO->x, DO->y) == glm::vec2(UP->x, UP->y)) || 
						prodU <= 0))
		{						
				if (!isTriangleDegenerate(glm::vec2(UP->x, UP->y), glm::vec2(DO->prev->x, DO->prev->y), glm::vec2(DO->x, DO->y)))
				{

					triangles.push_back(UP->index);
					triangles.push_back(DO->prev->index);
					triangles.push_back(DO->index);
					
				}
				DO = DO->prev;		
		}

	}
	return triangles;
}