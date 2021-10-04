#include <string>
#include "ShaderProgram.cpp"
#include "../Object/LightSource.cpp"
#include "../Camera/camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.cpp"

#ifndef MODEL
#define MODEL


class Model 
{
public:
    Model();
    Model(std::vector<Mesh> meshes, glm::vec3 colorFace, glm::vec3 colorEdge, glm::vec3 location, glm::vec3 scale, float rotAngleX, float rotAngleY, float rotAngleZ, GLenum renderingMode);
    void drawFaces(Shader& shader, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);
    void drawEdges(Shader& shader, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);
    void drawAll(Shader& shader, Shader& shaderEdges, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);
    void drawSelectMode(glm::vec3 color, Shader& shader, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);
    void drawOneMesh( Shader& shader, Shader& shaderEdges, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, int indexSelectmesh);
    void drawOneFace( Shader& shader, Shader& shaderEdges, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, int indexSelectmesh,int indexSelectFace);
    void drawOneVertex(Shader& shader, Shader& shaderEdges, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, const unsigned int indexSelectMesh,int indexSelectFace, int indexSelectVertex);
    void setPos(glm::vec3 vecPos);
    void setScale(glm::vec3 vecScale);
    void setRotation(float rotAngleX, float rotAngleY, float rotAngleZ);
    void setTranslateGeneralVertex(int indexMesh, int indexFace, int indexVertex,  glm::vec3 transVec);
    void rotateMesh(int indexCurMesh, glm::vec3 rotVector);
    void scaleAddMesh(int indexCurMesh, glm::vec3 scale);
    void rotate(float rotAngleX, float rotAngleY, float rotAngleZ);
    void scaleAdd(glm::vec3 scale);
    void setColorsFaces(glm::vec3 color);
    void setColorsEges(glm::vec3 color);
    void translateMesh(int indexCurMesh,glm::vec3 vector);
    glm::vec3 getColorsFaces();
    glm::vec3 getColorsEges();
    glm::vec3 getPos();
    void addMesh(Mesh newMesh);
    void deleteMesh(int index);
    void deleteFace(int indexMesh, int indexFaces);
    void deleteBufers();
    int getIndexSelectedFace(int indexMesh, Camera* camera);
    int getVertCountInFace(int indexMesh,int indexFace);
    int getFacesCount(int indexMesh);
    int getCountMeshes();
    void addInterVInFace(int indexMesh, int indexFace);
    void trianglateFace(int indexCurMesh, int indexCurFace);
private:
    std::vector<Mesh> meshes;
    glm::vec3 location;
    glm::vec3 scale;
    glm::vec3 colorFace;
    glm::vec3 colorEdges;
    float rotAngleX;
    float rotAngleY;
    float rotAngleZ;
    GLenum renderingMode;
};





#endif