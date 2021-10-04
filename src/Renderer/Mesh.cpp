#include <string>
#include "ShaderProgram.cpp"
#include "../Object/LightSource.cpp"
#include "../Camera/camera.h"
#include "../Triangulation/List.h"
#include "../Triangulation/Triangulation.cpp"


#ifndef MESH
#define MESH

struct Vertex 
{
    glm::vec3 position;
    glm::vec3 normal;
};
struct Edje
{
    std::vector<unsigned int>indexes;
    Edje(std::vector<unsigned int>indexes)
    {
        this->indexes = indexes;
    }
};
struct Face
{
    std::vector<unsigned int>indexes;
    Face(std::vector<unsigned int>indexes)
    {
        this->indexes = indexes;
    }
    Face() {}
};


class Mesh {
public:

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Face> indFaces;
    std::vector<Edje> indEdges;

    
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec3 location, glm::vec3 scale,float rotAngleX, float rotAngleY, float rotAngleZ)
    {
        this->vertices = vertices;
        this->indices = indices;

        this->scale = scale;
        this->location = location;
        this->rotAngleX = rotAngleX;
        this->rotAngleY = rotAngleY;
        this->rotAngleZ = rotAngleZ;
        setIndexesPolygonsAndEdgeI();
        setupMesh();
    }

    
    void draw(Shader shader, glm::vec3 objectColor, LightSourse lightSourse, Camera camera, int SCR_WIDTH, int SCR_HEIGHT,glm::mat4 modelMatrix,GLenum renderingMode)
    {
        shader.use();
        shader.setVec3("objectColor", objectColor);
        shader.setVec3("lightColor", lightSourse.getColor());
        shader.setVec3("lightPos", lightSourse.getPos());
        shader.setVec3("viewPos", camera.Position);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        shader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);
        modelMatrix =glm::translate(modelMatrix, location);
        modelMatrix =glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat4("model", modelMatrix);
        glBindVertexArray(VAO);
        int renderedIndexes = 0;
        for (int i = 0; i < indFaces.size(); i++)
        {
            glDrawElements(renderingMode, indFaces[i].indexes.size(), GL_UNSIGNED_INT, (void*)(renderedIndexes *sizeof(GL_UNSIGNED_INT)));
            renderedIndexes += indFaces[i].indexes.size();                               
        }      
        glBindVertexArray(0);
    }

    void drawOneFace(Shader shader, glm::vec3 objectColor, LightSourse lightSourse, Camera camera, int SCR_WIDTH, int SCR_HEIGHT, glm::mat4 modelMatrix, GLenum renderingMode, int index)
    {
        shader.use();
        shader.setVec3("objectColor", objectColor);
        shader.setVec3("lightColor", lightSourse.getColor());
        shader.setVec3("lightPos", lightSourse.getPos());
        shader.setVec3("viewPos", camera.Position);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        shader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);
        modelMatrix = glm::translate(modelMatrix, location);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f,0.0f,0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f,1.0f,0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f,0.0f,1.0f));
        shader.setMat4("model", modelMatrix);
        glBindVertexArray(VAO);
        int renderedIndexes = 0;
        for(int i=0;i<index;i++)
            renderedIndexes += indFaces[i].indexes.size();
            glDrawElements(renderingMode, indFaces[index].indexes.size(), GL_UNSIGNED_INT, (void*)(renderedIndexes * sizeof(GL_UNSIGNED_INT)));        
        glBindVertexArray(0);
    }
    
    void drawOneEdge(Shader shader, glm::vec3 objectColor, LightSourse lightSourse, Camera camera, int SCR_WIDTH, int SCR_HEIGHT, glm::mat4 modelMatrix, GLenum renderingMode, int index)
    {

    }
    void drawOneVertex(Shader shader, glm::vec3 objectColor, LightSourse lightSourse, Camera camera, int SCR_WIDTH, int SCR_HEIGHT, glm::mat4 modelMatrix, int indexSelectFace, int indexSelectVertex)
    {
        shader.use();
        shader.setVec3("objectColor", objectColor);
        shader.setVec3("lightColor", lightSourse.getColor());
        shader.setVec3("lightPos", lightSourse.getPos());
        shader.setVec3("viewPos", camera.Position);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        shader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);
        modelMatrix = glm::translate(modelMatrix, location);
        modelMatrix = glm::scale(modelMatrix, scale);
        modelMatrix = glm::rotate(modelMatrix, rotAngleX, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotAngleZ, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat4("model", modelMatrix);
        glBindVertexArray(VAO);
        glPointSize(10);
        int renderedIndexes = 0;
        for (int i = 0; i < indexSelectFace; i++)
            renderedIndexes += indFaces[i].indexes.size();

        glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, (void*)((renderedIndexes+indexSelectVertex)*sizeof(GL_UNSIGNED_INT)));
        glBindVertexArray(0);

    }

    void deleteBufer()
    {
        glDeleteBuffers(1, &VBO);
    }

    void deleteVertex()
    {

    }
    void deleteEdje()
    {

    }
    void deleteFace(int indexFace)
    {
        Face face = indFaces[indexFace];
        for (int i = 0; i < face.indexes.size(); i++)
        {
            vertices.erase(vertices.begin() + face.indexes[0]);
            indices.erase(indices.begin()+ indices.size() - 1);
        }
        for (int i = indexFace + 1; i < indFaces.size(); i++)
        {
            for (int j = 0; j < indFaces[i].indexes.size(); j++)
                indFaces[i].indexes[j] -= indFaces[indexFace].indexes.size();

        }
        indFaces.erase(indFaces.begin() + indexFace);

        /*for (auto v : vertices)
            std::cout << v.position.x << " " << v.position.y << " " << v.position.z << std::endl << std::endl;
        for (auto v : indices)
            std::cout << v << std::endl << std::endl;
        for (auto v : indFaces)
            for (auto i : v.indexes)
                std::cout << i<< std::endl;*/
        if(vertices.size()!=0)
            setupMesh();
    }


    void addVertex()
    {

    }
    void addEdje()
    {

    }
    void addPolygon(std::vector<Vertex>addVertex)
    {
        Face face;
        for (int i = 0; i < addVertex.size(); i++)
        {
            vertices.push_back(addVertex[i]);
            indices.push_back(indices.size()-1 + 1);// размер а не back
            face.indexes.push_back(indices.back());
        }
        indFaces.push_back(face);
    }

    void setTranslate(glm::vec3 vector)
    {
        location = vector;
    }
    void setRotangle(glm::vec3 rotVector)
    {
        rotAngleX = rotVector.x;
        rotAngleY = rotVector.y;
        rotAngleZ = rotVector.z;
    }
    void setScale(glm::vec3 scaleVector)
    {
        scale = scaleVector;
    }
    void scaleAdd(glm::vec3 scale)
    {
        this->scale += scale;
    }

    glm::vec3 getTranslate()
    {
        return location;
    }
    glm::vec3 getScale()
    {
        return scale;
    }
    float getRotAngleX()
    {
        return rotAngleX;
    }
    float getRotAngleY()
    {
        return rotAngleY;
    }
    float getRotAngleZ()
    {
        return rotAngleZ;
    }
    int getVertCountInFace(int indexFace)
    {
        return indFaces[indexFace].indexes.size();
    }
    int getFacesCount()
    {
        return indFaces.size();
    }
    glm::vec3 getVertexInFaceByIndex(int indexFace, int indexVertex)
    {
        return vertices[indFaces[indexFace].indexes[indexVertex]].position;
    }
    void setTranslateGeneralVertex(int indexFace, int indexVertex, glm::vec3 transVec) 
    {
        Vertex protVertex = vertices[indFaces[indexFace].indexes[indexVertex]];
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices[i].position == protVertex.position)
                vertices[i].position = transVec;
            setupMesh();
        }   
        
    }

    void trianglateFace(int indexFace)
    {
        std::vector<glm::vec2>firstVector;
        std::vector<Vertex>beginVertix;
        glm::vec2 tempVertex;
        Face face = indFaces[indexFace];
        List list;
        if (vertices[face.indexes[0]].normal.z != 0)
        {
            for (int i = face.indexes[0]; i <= face.indexes.back(); i++)
            {
                tempVertex = glm::vec2(vertices[i].position.x, vertices[i].position.y);
                firstVector.push_back(tempVertex);
                beginVertix.push_back(vertices[i]);
                
            }
                
        }
        else if (vertices[face.indexes[0]].normal.x != 0)
        {
            for (int i = face.indexes[0]; i <= face.indexes.back(); i++)
            {
                tempVertex = glm::vec2(vertices[i].position.y, vertices[i].position.z);
                firstVector.push_back(tempVertex);
                beginVertix.push_back(vertices[i]);
            }
        }
        else if (vertices[face.indexes[0]].normal.y != 0)
        {
            for (int i = face.indexes[0]; i <= face.indexes.back(); i++)
            {
                tempVertex = glm::vec2(vertices[i].position.x, vertices[i].position.z);
                firstVector.push_back(tempVertex);
                beginVertix.push_back(vertices[i]);
            }
        }
        list.insert(firstVector);
        std::vector<int>endIndexes = Triangulation::earClippingList(&list);
        //std::vector<int>endIndexes = Triangulation::triangulationMonotone(&list);
        deleteFace(indexFace);
        for (int i = 0; i < endIndexes.size() - 2; i+=3)
        {         
            std::vector <Vertex>tempTriangle = { beginVertix[endIndexes[i]],beginVertix[endIndexes[i+1]],beginVertix[endIndexes[i+2]] };
            addPolygon(tempTriangle);
        }
        setupMesh();
    }

    void addInterVInFace(int indexFace)
    {
        //Face face = indFaces[indexFace];
        glm::vec3 srPos;
        double srPosX;
        double srPosY;
        double srPosZ;
        int tempIndex;
        int shiftVertexInFace = indices.size();
        std::vector <Vertex>::iterator it;
        Vertex srVertex;
        srVertex.normal= vertices[indFaces[indexFace].indexes[0]].normal;
        for (int i = 0; i < indFaces[indexFace].indexes.size()-1; i+=2)
        {
            tempIndex = indFaces[indexFace].indexes[i];
            std::cout << "tempIndex    " << tempIndex << std::endl;
            srPosX = (vertices[tempIndex].position.x + vertices[tempIndex+1].position.x) / 2;
            srPosY = (vertices[tempIndex].position.y + vertices[tempIndex + 1].position.y) / 2;
            srPosZ = (vertices[tempIndex].position.z + vertices[tempIndex + 1].position.z) / 2;
            srPos = glm::vec3(srPosX, srPosY, srPosZ);
            std::cout << srPosX<< " " << srPosY <<" " << srPosZ << std::endl;
            it = vertices.begin() + tempIndex+1;
            srVertex.position = srPos;
            vertices.insert(it, srVertex);
            indices.push_back(indices.back()+1);
            indFaces[indexFace].indexes.push_back(indFaces[indexFace].indexes.back()+1);
        }
        tempIndex = indFaces[indexFace].indexes[indFaces[indexFace].indexes.size() - 1];
        srPosX = (vertices[indFaces[indexFace].indexes[0]].position.x + vertices[tempIndex].position.x) / 2;
        srPosY = (vertices[indFaces[indexFace].indexes[0]].position.y + vertices[tempIndex].position.y) / 2;
        srPosZ = (vertices[indFaces[indexFace].indexes[0]].position.z + vertices[tempIndex].position.z) / 2;
        srPos = glm::vec3(srPosX, srPosY, srPosZ);
        it = vertices.begin() + tempIndex+1;
        std::cout << srPosX << " " << srPosY << " " << srPosZ << std::endl;
        srVertex.position = srPos;
        vertices.insert(it, srVertex);
        indices.push_back(indices.back()+1);
        indFaces[indexFace].indexes.push_back(indFaces[indexFace].indexes.back()+1);
        shiftVertexInFace = indices.size()- shiftVertexInFace;
        std::cout << "  shiftVertexInFace " << shiftVertexInFace <<std::endl;

        for (int i = indexFace+1; i < indFaces.size(); i++)
            for (int j = 0; j < indFaces[i].indexes.size(); j++)
                indFaces[i].indexes[j] += shiftVertexInFace;
        setupMesh();
       
    }
    void ShowInfo()
    {
        std::cout << "VERTEX:" << std::endl;
       for(auto v:vertices)
           std::cout << "   " <<v.position.x<< "   " << v.position.y << "   " << v.position.z << std::endl << std::endl;
       std::cout << "INDEXES:" << std::endl;
       for (auto i : indices)
           std::cout << "   "<<i << std::endl << std::endl;
       std::cout << "FACES:" << std::endl;
       for(int i=0;i<indFaces.size();i++)
       {
           std::cout << "  " << i << std::endl << std::endl;
           for (int j=0;j<indFaces[i].indexes.size();j++)
           {
               std::cout << "    " << indFaces[i].indexes[j] <<std::endl << std::endl;
           }
       }
          
    }

protected:
    // Данные для рендеринга
    unsigned int VAO, VBO, EBO;
    glm::vec3 location;
    
    glm::vec3 scale;
    float rotAngleX;
    float rotAngleY;
    float rotAngleZ;
    void setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
            &indices[0], GL_STATIC_DRAW);

        // Координаты вершин
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // Нормали вершин
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));   

        glBindVertexArray(0);
    }
    void setIndexesPolygonsAndEdgeI()
    {
        std::vector<unsigned int>v0{ 0 };
        Face newFace(v0);
        Edje newEdge(v0);
        indFaces.push_back(newFace);
        indEdges.push_back(newEdge);
        for (unsigned int i = 1; i < indices.size(); i++)
        {
            if (vertices[indices[i]].normal == vertices[indices[i - 1]].normal)
            {
                indFaces.back().indexes.push_back(indices[i]);
                if (indEdges.back().indexes.size() == 1)
                {
                    indEdges.back().indexes.push_back(indices[i]);
                }
                else
                {
                    std::vector<unsigned int>vTemp{ indices[i - 1], indices[i] };
                    Edje tempEdge(vTemp);
                    indEdges.push_back(tempEdge);
                }
            }
            else
            {
                std::vector<unsigned int>vTemp{ indices[i] };
                Face tempFace(vTemp);
                indFaces.push_back(tempFace);
                Edje tempEdge(vTemp);
                indEdges.push_back(tempEdge);
            }


        }
    }
};


#endif