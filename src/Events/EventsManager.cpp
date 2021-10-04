#include <string>
#include "../Renderer/ShaderProgram.cpp"
#include "../Object/LightSource.cpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#ifndef EVENTS_MANAGER
#define EVENTS_MANAGER

enum  TYPES_CREATING {
	CubeCreating, SphereCreating, CylinderCreating, PyramiCreatingd, PrizmaCreating
};
enum TYPES_OBJECT {
	Models,Meshes, Faces, Edges, Vertexes
};

enum TYPES_OPERATION {
	Create, Select, Translate, Scale, Rotation
};

 class EventsManager {
public:
	EventsManager()
	{		
		typeCreate = TYPES_CREATING(CubeCreating);
		typeObject = TYPES_OBJECT(Models);
		typeOperation = TYPES_OPERATION(Select);
	}
	
	 TYPES_CREATING typeCreate;
	 TYPES_OBJECT typeObject;
	 TYPES_OPERATION typeOperation;
};

#endif