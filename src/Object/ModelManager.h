#include <string>
#include "../Renderer/ShaderProgram.cpp"
#include "../Object/LightSource.cpp"
#include "../Camera/camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Renderer/Mesh.cpp"
#include "../Renderer/Model.cpp"
#include "../Events/EventsManager.cpp"



#ifndef MODEL_MANAGER
#define MODEL_MANAGER


 class ModelManager {

public:
	
	ModelManager(Camera *camera);
	ModelManager(std::vector<Model>models, LightSourse lightSourse, Camera* camera);
	void drawAll(EventsManager eManager);
	void drawByIndex(int index);
	void addModel(Model model);
	void translate(glm::vec3 transVector);
	void setScale(glm::vec3 scaleVector);
	void rotate(glm::vec3 rotanglesXYZ);
	void scaleAdd(glm::vec3 scale);
	void createGrid();
	void createAim();
	void setSelectMode(bool flag);
	void setIndexCurModel(int index);
	void setIndexCurMesh(int index);
	void setIndexCurFace(int index);
	void setIndexCurVertex(int index);
	void deleteBufers();
	void setLocation(glm::vec3 transVector);
	int getIndexCurModel();
	int getIndexCurMesh();
	int getIndexCurFace();
	int getIndexCurVertex();
	void selectFace();
	void deleteSelected();
	void selectPrev();
	void selectNext();
	void addIntermediateVertexes();
	void triangulate();
	void copy();
private:
	Camera *camera;
	std::vector<Model>models;
	LightSourse lightSourse;
	int indexCurEdge;
	int indexCurVertex;
	int indexCurModel;
	int indexCurMesh;
	int indexCurFace;

	Shader shader;
	Shader shaderEdges;
	Shader shaderScreen;

	const unsigned int SCR_WIDTH;
	const unsigned int SCR_HEIGHT;
	Model grid;
	Model aim;
	bool isTheGridDrawn;
	bool selectMode = false;
};

#endif

