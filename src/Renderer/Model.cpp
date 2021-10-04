#include <string>
#include "ShaderProgram.cpp"
#include "../Object/LightSource.cpp"
#include "../Camera/camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.cpp"
#include "../AlgGeometric/AlgGeometric.h"

#ifndef MODEL
#define MODEL


class Model
{
public:
    Model() {};
    Model(std::vector<Mesh> meshes, glm::vec3 colorFace, glm::vec3 colorEdge, glm::vec3 location, glm::vec3 scale, float rotAngleX, float rotAngleY, float rotAngleZ, GLenum renderingMode)
    {
        this->meshes = std::vector(meshes);
        this->location = location;
        this->scale = scale;
        this->rotAngleX = rotAngleX;
        this->rotAngleY = rotAngleY;
        this->rotAngleZ = rotAngleZ;
        this->renderingMode = renderingMode;
        this->colorFaces = colorFace;
        this->colorEdges = colorEdge;

    }
    void drawFaces(Shader& shader, LightSourse lightSourse,Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, location);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f, 0.0f, 1.0f));
        for (int i = 0; i < meshes.size(); i++)
        {
            meshes[i].draw(shader, colorFaces, lightSourse, camera, SCR_WIDTH, SCR_HEIGHT, modelMatrix,renderingMode);
        }
    }
    void drawEdges(Shader& shader, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, location);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f, 0.0f, 1.0f));
        for (int i = 0; i < meshes.size(); i++)
        {
            meshes[i].draw(shader, colorEdges, lightSourse, camera, SCR_WIDTH, SCR_HEIGHT, modelMatrix, GL_LINE_LOOP);
        }
    }
    void drawAll(Shader& shader, Shader& shaderEdges, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
    {
        drawFaces(shader, lightSourse,camera, SCR_WIDTH,SCR_HEIGHT);
        drawEdges(shaderEdges, lightSourse,camera, SCR_WIDTH,SCR_HEIGHT);
    }
    
    void drawOneMesh(Shader& shader, Shader& shaderEdges, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, int indexSelectmesh)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, location);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f, 0.0f, 1.0f));
        meshes[indexSelectmesh].draw(shader, colorFaces, lightSourse, camera, SCR_WIDTH, SCR_HEIGHT, modelMatrix, renderingMode);
        meshes[indexSelectmesh].draw(shaderEdges, colorEdges, lightSourse, camera, SCR_WIDTH, SCR_HEIGHT, modelMatrix, GL_LINE_LOOP); 
    }

    void drawOneFace(Shader& shader, Shader& shaderEdges, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, int indexSelectmesh, int indexSelectFace)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, location);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f, 0.0f, 1.0f));
        meshes[indexSelectmesh].drawOneFace(shader, colorFaces, lightSourse, camera, SCR_WIDTH, SCR_HEIGHT, modelMatrix, renderingMode, indexSelectFace);
        meshes[indexSelectmesh].drawOneFace(shaderEdges, colorEdges, lightSourse, camera, SCR_WIDTH, SCR_HEIGHT, modelMatrix, GL_LINE_LOOP, indexSelectFace);
    }

    void drawOneVertex(Shader& shader, Shader& shaderEdges, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT, const unsigned int indexSelectMesh, int indexSelectFace, int indexSelectVertex)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, location);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f, 0.0f, 1.0f));
        meshes[indexSelectMesh].drawOneVertex(shader, colorEdges, lightSourse, camera, SCR_WIDTH, SCR_HEIGHT, modelMatrix, indexSelectFace, indexSelectVertex);
    }

    void drawSelectMode(glm::vec3 color, Shader& shader, LightSourse lightSourse, Camera camera, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, location);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f, 0.0f, 1.0f));
        for (int i = 0; i < meshes.size(); i++)
        {
            color.y=0.01f * (i + 1);//y x
            meshes[i].draw(shader, color, lightSourse, camera, SCR_WIDTH, SCR_HEIGHT, modelMatrix, renderingMode);
        }
    }

    void setPos(glm::vec3 vecPos)
    {
        this->location = glm::vec3(vecPos.x, vecPos.y, vecPos.z );
    }

    void setScale(glm::vec3 vecScale) 
    {
        this->scale= glm::vec3(vecScale.x, vecScale.y, vecScale.z);
    }
    void setRotation(float rotAngleX, float rotAngleY, float rotAngleZ )
    {
       
        this->rotAngleX = rotAngleX;
        this->rotAngleY = rotAngleY;
        this->rotAngleZ = rotAngleZ;
    }

    void setTranslateGeneralVertex(int indexMesh, int indexFace, int indexVertex, glm::vec3 transVec)
    {
        glm::vec3 beginPoint = meshes[indexMesh].getVertexInFaceByIndex(indexFace, indexVertex);
        meshes[indexMesh].setTranslateGeneralVertex( indexFace,  indexVertex, beginPoint+transVec);
    }
    void rotate(float rotAngleX, float rotAngleY, float rotAngleZ)
    {

        this->rotAngleX += rotAngleX;
        this->rotAngleY += rotAngleY;
        this->rotAngleZ += rotAngleZ;
    }
    void rotateMesh(int indexCurMesh, glm::vec3 rotVector)
    {
        glm::vec3 oldAngleVector(meshes[indexCurMesh].getRotAngleX(), meshes[indexCurMesh].getRotAngleY(), meshes[indexCurMesh].getRotAngleZ());
        meshes[indexCurMesh].setRotangle(oldAngleVector+rotVector);
    }
    void translateMesh(int indexCurMesh, glm::vec3 vector)
    {
        meshes[indexCurMesh].setTranslate(meshes[indexCurMesh].getTranslate() + vector);
    }
    void scaleAddMesh(int indexCurMesh, glm::vec3 scale)
    {
        meshes[indexCurMesh].setScale(meshes[indexCurMesh].getScale() + scale);
    }
    void scaleAdd(glm::vec3 scale)
    {
        this->scale += scale;
    }
    void setColorsFaces(glm::vec3 color)
    {
        this->colorFaces= glm::vec3(color.x, color.y, color.z);
    }
    void setColorsEges(glm::vec3 color)
    {
        this->colorEdges= glm::vec3(color.x, color.y, color.z);
    }

    glm::vec3 getColorsFaces()
    {
        return this->colorFaces;
    }
    glm::vec3 getColorsEges()
    {
        return this->colorEdges;
    }
    glm::vec3 getPos()
    {
        return this->location;
    }
    void addMesh(Mesh newMesh)
    {
        meshes.push_back(newMesh);
    }
    void deleteMesh(int index) 
    {
        meshes.erase(meshes.begin() + index);
    }
    void deleteFace(int indexMesh, int indexFaces)
    {
        meshes[indexMesh].deleteFace(indexFaces);
    }
    void deleteBufers()
    {
        for (int i = 0; i < meshes.size(); i++)
            meshes[i].deleteBufer();
    }

    int getIndexSelectedFace(int indexMesh, Camera *camera)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, location);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f, 0.0f, 1.0f));
        
        glm::vec3 result;
        int tempIndexFace = -1;
        for (int i = 0; i < meshes[indexMesh].indFaces.size(); i++)
        {
            result=AlgGeometric::getPointFaceAndVector(meshes[indexMesh], i, &(*camera), modelMatrix);
            if (result != glm::vec3(10000, 10000, 10000))
            {
                tempIndexFace = i;
                break;
            }            
        }
        std::cout << "index Face:" << tempIndexFace << std::endl;
        return tempIndexFace;
    }
    int getVertCountInFace(int indexMesh, int indexFace)
    {
        return meshes[indexMesh].getVertCountInFace(indexFace);
    }
    int getFacesCount(int indexMesh)
    {
        return meshes[indexMesh].getFacesCount();
    }
    int getCountMeshes()
    {
        return meshes.size();
    }
    void addInterVInFace(int indexMesh, int indexFace)
    {
        meshes[indexMesh].addInterVInFace(indexFace);
    }
    void trianglateFace(int indexCurMesh, int indexCurFace)
    {
        meshes[indexCurMesh].trianglateFace(indexCurFace);
    }

private:
    std::vector<Mesh> meshes;
    glm::vec3 location;
    glm::vec3 scale;
    glm::vec3 colorFaces;
    glm::vec3 colorEdges;
    float rotAngleX;
    float rotAngleY;
    float rotAngleZ;
    GLenum renderingMode;
};
#endif