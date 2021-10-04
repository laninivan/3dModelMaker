#include <string>
#include "ShaderProgram.cpp"
#include "../Object/LightSource.cpp"
#include "../Camera/camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef MESH
#define MESH

struct Vertex;
struct Face;
struct Edje;

class Mesh {
public:

    // Mesh-данные
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Face> indFaces;
    std::vector<Edje> indEdges;

   

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 location, glm::vec3 scale, float rotAngleX, float rotAngleY, float rotAngleZ);
    void draw(Shader shader, glm::vec3 objectColor, LightSourse lightSourse, Camera camera, int SCR_WIDTH, int SCR_HEIGHT, glm::mat4 modelMatrix, GLenum renderingMode);
    void drawOneFace(Shader shader, glm::vec3 objectColor, LightSourse lightSourse, Camera camera, int SCR_WIDTH, int SCR_HEIGHT, glm::mat4 modelMatrix, GLenum renderingMode,int index);
    void drawOneEdge(Shader shader, glm::vec3 objectColor, LightSourse lightSourse, Camera camera, int SCR_WIDTH, int SCR_HEIGHT, glm::mat4 modelMatrix, GLenum renderingMode, int index);
    void drawOneVertex(Shader shader, glm::vec3 objectColor, LightSourse lightSourse, Camera camera, int SCR_WIDTH, int SCR_HEIGHT, glm::mat4 modelMatrix, int indexSelectFace, int indexSelectVertex);

    void deleteBufer();
    void deleteVertex();
    void deleteEdje();
    void deleteFace(int indexFace);


    void addVertex();
    void addEdje();
    void addPolygon(std::vector<Vertex>addVertex);
    void setTranslate(glm::vec3 vector);
    void setRotangle(glm::vec3 rotVector);
    void setScale(glm::vec3 scaleVector);
    void scaleAdd(glm::vec3 scale);
    glm::vec3 getTranslate();
    glm::vec3 getScale();
    float getRotAngleX();
    float getRotAngleY();
    float getRotAngleZ();
    int getVertCountInFace(int indexFace);
    glm::vec3 getVertexInFaceByIndex(int indexFace, int indexVertex);
    int getFacesCount();
    
    void setTranslateGeneralVertex(int indexFace, int indexVertex, glm::vec3 transVec);
    void addInterVInFace(int indexFace);
    void trianglateFace(int indexFace);
    void ShowInfo();
protected:
    // Данные для рендеринга
    unsigned int VAO, VBO, EBO;
    glm::vec3 location;
   
    glm::vec3 scale;
    float rotAngleX;
    float rotAngleY;
    float rotAngleZ;

    void setupMesh();
    void setIndexesPolygonsAndEdgeI();

    
};


#endif