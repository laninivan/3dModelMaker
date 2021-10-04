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
#include <numeric>
#include "../Events/EventsManager.cpp"
#include "../AlgGeometric/AlgGeometric.h"


#ifndef MODEL_MANAGER
#define MODEL_MANAGER


 class ModelManager {

public:
	ModelManager(Camera* camera)
	{
		this->lightSourse = LightSourse();
		this->indexCurModel = -1;
		this->indexCurMesh = -1;
		this->indexCurFace = -1;
		this->indexCurEdge = -1;;
		this->indexCurVertex = -1;;
		this->shader = Shader("../src/shader.vs", "../src/shader.fs");
		this->shaderEdges = Shader("../src/shader.vs", "../src/shaderNoGlare.fs");
		this->shaderScreen = Shader("../src/shaderScreen.vs", "../src/shaderNoGlare.fs");
		this->camera = (camera);
		createGrid();
		createAim();
		isTheGridDrawn = true;
		selectMode = false;
	};
	ModelManager(std::vector<Model>models, LightSourse lightSourse, Camera* camera)
	{
		this->models = std::vector(models);
		this->lightSourse = lightSourse;
		this->indexCurModel =  - 1;
		this->indexCurMesh =  - 1;
		this->indexCurFace =  - 1;
		this->indexCurEdge = -1;;
		this->indexCurVertex = -1;;
		this->shader = Shader("../src/shader.vs", "../src/shader.fs");
		this->shaderEdges = Shader("../src/shader.vs", "../src/shaderNoGlare.fs");
		this->shaderScreen = Shader("../src/shaderScreen.vs", "../src/shaderNoGlare.fs");

		this->camera = &(*camera);
		createGrid();
		createAim();
		isTheGridDrawn = true;
		selectMode = false;

	}
	void drawAll(EventsManager eManager)
	{			
		glLineWidth(1);
		if (selectMode)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (int i = 0; i < models.size(); i++)
			{
				models[i].drawSelectMode(glm::vec3(0.01f*(i+1),0.0f,0.0f), shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);
			}
		}	
		else
		{	
			glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (isTheGridDrawn)
				grid.drawFaces(shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);

			if (indexCurModel != -1)
			{
				glLineWidth(4);
				glm::vec3 tempColorFaces = models[indexCurModel].getColorsFaces();
				glm::vec3 tempColorEdges = models[indexCurModel].getColorsEges();

				models[indexCurModel].setColorsEges(glm::vec3(1.0f, 0.3f, 0.0));
				models[indexCurModel].setColorsFaces(glm::vec3(0.3f, 0.2f, 0.0));

				if (eManager.typeObject == TYPES_OBJECT(Models) && indexCurModel != -1)
				{
					models[indexCurModel].drawAll(shaderEdges, shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);
				}

				if (eManager.typeObject == TYPES_OBJECT(Meshes) && indexCurModel != -1 && indexCurMesh != -1)
				{
					models[indexCurModel].drawOneMesh(shaderEdges, shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT, indexCurMesh);
				}

				if (eManager.typeObject == TYPES_OBJECT(Faces) && indexCurModel != -1 &&indexCurMesh!=-1 && indexCurFace!=-1)
				{
					models[indexCurModel].drawOneFace(shaderEdges, shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT, indexCurMesh, indexCurFace);
				}
				if (eManager.typeObject == TYPES_OBJECT(Edges) && indexCurModel != -1 && indexCurMesh != -1 && indexCurFace != -1 && indexCurEdge != -1)
				{

				}
				if (eManager.typeObject == TYPES_OBJECT(Vertexes) && indexCurModel != -1 && indexCurMesh != -1 && indexCurFace != -1 && indexCurVertex != -1)
				{
					models[indexCurModel].drawOneVertex(shaderEdges, shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT, indexCurMesh, indexCurFace,indexCurVertex);
				}
				models[indexCurModel].setColorsEges(tempColorEdges);
				models[indexCurModel].setColorsFaces(tempColorFaces);
				glLineWidth(1);
			}


			for (int i = 0; i < models.size(); i++)
			{
				models[i].drawAll(shader,shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);
			}							
			glLineWidth(0.25f);
			aim.drawFaces(shaderScreen, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);
		}
		
	}
	void drawByIndex(int index)
	{
		if (isTheGridDrawn)
			grid.drawFaces(shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);
		glLineWidth(1);
		models[index].drawAll(shader, shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);
		glLineWidth(0.25f);
		aim.drawFaces(shaderScreen, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);

	}
	void addModel(Model model) 
	{
		models.push_back(model);
		indexCurModel = models.size() - 1;
	}
	void setLocation(glm::vec3 transVector)
	{
		models[indexCurModel].setPos(transVector);
	}

	
	void setScale(glm::vec3 scaleVector)
	{
		models[indexCurModel].setScale(scaleVector);
	}
	void translate(glm::vec3 transVector)
	{
		if (indexCurVertex != -1)
		{
			models[indexCurModel].setTranslateGeneralVertex(indexCurMesh,indexCurFace,indexCurVertex,transVector);
		}
		else if (indexCurMesh != -1)
		{		
			models[indexCurModel].translateMesh(indexCurMesh,transVector);
		}
		else if (indexCurModel != -1)
		{
			glm::vec3 pos = models[indexCurModel].getPos();
			models[indexCurModel].setPos(pos + transVector);
		}		
	}
	void rotate(glm::vec3 rotanglesXYZ)
	{
		if (indexCurMesh != -1)
		{
			models[indexCurModel].rotateMesh(indexCurMesh, rotanglesXYZ);
		}
		else if(indexCurModel!=-1)
			models[indexCurModel].rotate(rotanglesXYZ.x, rotanglesXYZ.y, rotanglesXYZ.z);
	}
	void scaleAdd(glm::vec3 scale)
	{
		if (indexCurMesh != -1)
		{
			models[indexCurModel].scaleAddMesh(indexCurMesh, scale);
		}
		else if (indexCurModel != -1)
			models[indexCurModel].scaleAdd(scale);
	}
	void setSelectMode(bool flag)
	{
		selectMode = flag;
	}
	void setIndexCurModel(int index)
	{
		indexCurModel = index;
	}
	void setIndexCurMesh(int index)
	{
		if (indexCurModel != -1)
		{
			indexCurMesh = index;
		}		
	}
	void setIndexCurFace(int index)
	{
		if (indexCurModel != -1 && indexCurMesh != -1)
			indexCurFace = index;
	}
	void setIndexCurVertex(int index)
	{
		indexCurVertex = index;
	}
	int getIndexCurModel()
	{
		return indexCurModel;
	}
	int getIndexCurMesh()
	{
		return indexCurMesh;
	}
	int getIndexCurFace()
	{
		return indexCurFace;
	}
	int getIndexCurVertex()
	{
		return indexCurVertex;
	}

	void deleteBufers()
	{
		for (int i = 0; i < models.size(); i++)
			models[i].deleteBufers();
	}

	void selectFace()
	{
		if(indexCurMesh!=-1)
		indexCurFace=models[indexCurModel].getIndexSelectedFace(indexCurMesh, camera);
	}
	void deleteSelected()
	{
		if (indexCurFace != -1)
		{
			models[indexCurModel].deleteFace(indexCurMesh, indexCurFace);
			indexCurFace = -1;
			std::cout << "DELETE FACE" << std::endl;
		}
		else if (indexCurMesh != -1)
		{
			models[indexCurModel].deleteMesh(indexCurMesh);
			indexCurMesh = -1;
			std::cout << "DELETE MESH" << std::endl;
		}
		else if (indexCurModel != -1)
		{
			models.erase(models.begin() + indexCurModel);
			indexCurModel = -1;
			std::cout << "DELETE MODEL" << std::endl;
		}
	}

	void selectPrev()
	{
		if (indexCurVertex != -1)
		{
			if (indexCurVertex != 0)
				indexCurVertex--;
		}
		else if (indexCurFace != -1)
		{
			if(indexCurFace != 0)
				indexCurFace--;
		}
		else if (indexCurMesh != -1 )
		{
			if(indexCurMesh != 0)
				indexCurMesh--;
		}
		else if (indexCurModel != -1)
		{
			if(indexCurModel != 0)
				indexCurModel--;
		}
	}
	void selectNext()
	{
		if (indexCurVertex != -1)
		{
			if (indexCurVertex < models[indexCurModel].getVertCountInFace(indexCurMesh,indexCurFace) - 1)
				indexCurVertex++;
		}
		else if (indexCurFace != -1 )
		{
			if(indexCurFace < models[indexCurModel].getFacesCount(indexCurMesh) - 1)
				indexCurFace++;
		}
		else if (indexCurMesh != -1 )
		{
			if(indexCurMesh < models[indexCurModel].getCountMeshes() - 1)
				indexCurMesh++;
		}
		else if (indexCurModel != -1 )
		{
			if(indexCurModel < models.size() - 1)
				indexCurModel++;
		}
	}
	void  addIntermediateVertexes()
	{
		if (indexCurFace != -1)
		{
			models[indexCurModel].addInterVInFace(indexCurMesh, indexCurFace);
		}
		else if (indexCurMesh != -1)
		{
			
		}
		else if (indexCurModel != -1)
		{

		}	
	}
	void triangulate()
	{
		if (indexCurFace != -1)
		{
			models[indexCurModel].trianglateFace(indexCurMesh, indexCurFace);
		}
		else if (indexCurMesh != -1)
		{

		}
		else if (indexCurModel != -1)
		{

		}
	}
	void copy()
	{
		if (indexCurFace != -1)
		{
			
		}
		else if (indexCurMesh != -1)
		{

		}
		else if (indexCurModel != -1)
		{
			models.push_back(models[indexCurModel]);
		}
	}

private:
	Camera *camera;
	std::vector<Model>models;
	LightSourse lightSourse;

	Shader shader;
	Shader shaderEdges;
	Shader shaderScreen;
	const unsigned int SCR_WIDTH=800;
	const unsigned int SCR_HEIGHT=600;
	int indexCurModel;
	int indexCurMesh;
	int indexCurFace;
	int indexCurEdge;
	int indexCurVertex;
	Model grid;
	Model aim;
	bool selectMode;
	bool isTheGridDrawn;
	void createGrid()
	{
		std::vector<Vertex> verticesGrid;
		for (float i = -10.f; i <= 10.f; i += 0.5f)
		{
			verticesGrid.push_back({ glm::vec3(-10.0f, i, 0.0f), glm::vec3(0.0f,  0.0f, 1.0f) });
			verticesGrid.push_back({ glm::vec3(10.0f, i, 0.0f), glm::vec3(0.0f,  0.0f, 1.0f) });

			verticesGrid.push_back({ glm::vec3(i, -10.0f, 0.0f), glm::vec3(0.0f,  0.0f, 1.0f) });
			verticesGrid.push_back({ glm::vec3(i, 10.0f, 0.0f), glm::vec3(0.0f,  0.0f, 1.0f) });
		}
		std::vector<unsigned int> indicesGrid(verticesGrid.size());
		std::iota(indicesGrid.begin(), indicesGrid.end(), 0);
		Mesh meshGrig(verticesGrid, indicesGrid, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.0f, 0.0f, 0.0f);
		std::vector<Mesh>meshesGrid = { meshGrig };
		this->grid = Model(meshesGrid, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.0f, 0.0f, 0.0f, GL_LINES);
	}
	void createAim()
	{
		std::vector<Vertex> verticesAim = {
			{glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.0f,  0.0f, 0.0f)},			
			{glm::vec3(0.0f,-0.05f, 0.0f), glm::vec3(0.0f,  0.0f, 0.0f)},
			{glm::vec3(0.05f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, 0.0f)},
			{glm::vec3(-0.05f,0.0f, 0.0f), glm::vec3(0.0f,  0.0f, 0.0f)},
		};
		
		std::vector<unsigned int> indicesAim = {0,1,2,3};
		
		Mesh meshAim(verticesAim, indicesAim, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.0f, 0.0f, 0.0f);
		std::vector<Mesh>meshesAim = { meshAim };
		this->aim = Model(meshesAim, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.0f, 0.0f, 0.0f, GL_LINES);
	}

};


#endif