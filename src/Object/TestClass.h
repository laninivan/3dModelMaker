#ifndef TEST_H
#define TEST_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


// јбстрактный класс камеры, который обрабатывает входные данные и вычисл€ет соответствующие Ёйлеровы углы, векторы и матрицы дл€ использовани€ в OpenGL
//Camera cam(glm::vec3(1.0f, 1.0f, 1.0f));
class Test {

public:
	Test(glm::vec3 a= glm::vec3(1,1,1))
	{
		this->lightSourse = LightSourse();
		this->indexCurModel = 0;
		this->shader = Shader("../src/shader.vs", "../src/shader.fs");
		this->shaderEdges = Shader("../src/shader.vs", "../src/shaderNoGlare.fs");
		this->shaderScreen = Shader("../src/shaderScreen.vs", "../src/shaderNoGlare.fs");
		this->camera = (camera);
		createGrid();
		createAim();
		isTheGridDrawn = true;
		selectMode = false;
	};
	Test(std::vector<Model>models, LightSourse lightSourse, Camera* camera)
	{
		this->models = std::vector(models);
		this->lightSourse = lightSourse;
		this->indexCurModel = models.size() - 1;
		this->shader = Shader("../src/shader.vs", "../src/shader.fs");
		this->shaderEdges = Shader("../src/shader.vs", "../src/shaderNoGlare.fs");
		this->shaderScreen = Shader("../src/shaderScreen.vs", "../src/shaderNoGlare.fs");

		this->camera = &(*camera);
		createGrid();
		createAim();
		isTheGridDrawn = true;
		selectMode = false;

	}
	void drawAll()
	{


		glLineWidth(1);
		if (selectMode)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (int i = 0; i < models.size(); i++)
			{
				models[i].drawSelectMode(glm::vec3(0.01f * (i + 1)), shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);
			}
		}
		else
		{


			glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (isTheGridDrawn)
				grid.drawFaces(shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);

			for (int i = 0; i < models.size(); i++)
			{

				if (i == indexCurModel)
				{
					glLineWidth(4);
					glm::vec3 tempColorFaces = models[i].getColorsFaces();
					glm::vec3 tempColorEdges = models[i].getColorsEges();

					models[i].setColorsEges(glm::vec3(1.0f, 0.3f, 0.0));
					models[i].setColorsFaces(tempColorFaces * 2.0f);
					models[i].setColorsFaces(tempColorFaces * 2.0f);
					models[i].drawAll(shader, shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);
					models[i].setColorsEges(tempColorEdges);
					models[i].setColorsFaces(tempColorFaces);
					glLineWidth(1);
				}
				else models[i].drawAll(shader, shaderEdges, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);

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
		/*glLineWidth(0.25f);
		aim.drawFaces(shaderScreen, lightSourse, (*camera), SCR_WIDTH, SCR_HEIGHT);*/

	}
	void addModel(Model model)
	{
		models.push_back(model);
		indexCurModel = models.size() - 1;
	}
	void deleteModel()
	{
		models.erase(models.begin() + indexCurModel);
	}
	void transform(glm::vec3 transVector)
	{
		models[indexCurModel].setPos(transVector);
	}
	void scale(glm::vec3 scaleVector)
	{
		models[indexCurModel].setScale(scaleVector);
	}
	void rotation(glm::vec3 rotareVector, float value)
	{
		models[indexCurModel].setRotation(rotareVector, value);
	}
	void setSelectMode(bool flag)
	{
		selectMode = flag;
	}
	void setIndexCurModel(int index)
	{
		indexCurModel = index;
	}
private:
	Camera* camera;
	std::vector<Model>models;
	LightSourse lightSourse;
	int indexCurModel;
	Shader shader;
	Shader shaderEdges;
	Shader shaderScreen;
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
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
		Mesh meshGrig(verticesGrid, indicesGrid, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0), 0.f);
		std::vector<Mesh>meshesGrid = { meshGrig };
		this->grid = Model(meshesGrid, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0), 0.0f, GL_LINES);
	}
	void createAim()
	{
		std::vector<Vertex> verticesAim = {
			{glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.0f,  0.0f, 0.0f)},
			{glm::vec3(0.0f,-0.05f, 0.0f), glm::vec3(0.0f,  0.0f, 0.0f)},
			{glm::vec3(0.05f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, 0.0f)},
			{glm::vec3(-0.05f,0.0f, 0.0f), glm::vec3(0.0f,  0.0f, 0.0f)},
		};

		std::vector<unsigned int> indicesAim = { 0,1,2,3 };

		Mesh meshAim(verticesAim, indicesAim, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0), 0.f);
		std::vector<Mesh>meshesAim = { meshAim };
		this->aim = Model(meshesAim, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0), 0.0f, GL_LINES);
	}

};



#endif