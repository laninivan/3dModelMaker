#include <string>
#include "../Renderer/ShaderProgram.cpp"
#include "../Object/LightSource.cpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#ifndef EVENTS_MANAGER
#define EVENTS_MANAGER

enum TYPES_CREATING;
enum TYPES_OBJECT;
enum TYPES_OPERATION;

 class EventsManager{
public:
	EventsManager();

	 TYPES_CREATING typeCreate;
	 TYPES_OBJECT typeObject;
	 TYPES_OPERATION typeOperation;


};

#endif