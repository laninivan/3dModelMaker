#include <string>
#include "../Renderer/ShaderProgram.cpp"
#include "../Object/LightSource.cpp"
#include "../Camera/camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Renderer/Mesh.cpp"

#ifndef CUBE
#define CUBE

class Cube :public Mesh {

public:
    Cube(double radius, glm::vec3 location, glm::vec3 scale, float rotAngleX, float rotAngleY, float rotAngleZ): Mesh(generVertexes(radius), generIndices(), location, scale, rotAngleX,  rotAngleY,  rotAngleZ)
    {
        this->radius = radius;           
    };

private:
    std::vector<Vertex> generVertexes(double radius)
    {
       
       std::vector<Vertex> vertices = {
           {glm::vec3(-radius,-radius, -radius),glm::vec3(0.0f,  0.0f, -1.0f)},
           {glm::vec3(radius,-radius, -radius), glm::vec3(0.0f,  0.0f, -1.0f)},
           {glm::vec3(radius,radius, -radius),  glm::vec3(0.0f,  0.0f, -1.0f)},
           {glm::vec3(-radius,radius, -radius), glm::vec3(0.0f,  0.0f, -1.0f)},

           {glm::vec3(-radius,-radius, radius), glm::vec3(0.0f,  0.0f, 1.0f)},
           {glm::vec3(-radius,radius, radius),  glm::vec3(0.0f,  0.0f, 1.0f)},
           {glm::vec3(radius,radius, radius),   glm::vec3(0.0f,  0.0f, 1.0f)},
           {glm::vec3(radius,-radius, radius),  glm::vec3(0.0f,  0.0f, 1.0f)},

           {glm::vec3(-radius,-radius, -radius),glm::vec3(-1.0f,  0.0f, 0.0f)},
           {glm::vec3(-radius,radius, -radius), glm::vec3(-1.0f,  0.0f, 0.0f)},
           {glm::vec3(-radius,radius, radius),  glm::vec3(-1.0f,  0.0f, 0.0f)},
           {glm::vec3(-radius,-radius, radius), glm::vec3(-1.0f,  0.0f, 0.0f)},

           {glm::vec3(radius,-radius, -radius), glm::vec3(1.0f,  0.0f, 0.0f)},
           {glm::vec3(radius,-radius, radius),  glm::vec3(1.0f,  0.0f, 0.0f)},
           {glm::vec3(radius,radius, radius),   glm::vec3(1.0f,  0.0f, 0.0f)},
           {glm::vec3(radius,radius, -radius),  glm::vec3(1.0f,  0.0f, 0.0f)},

           {glm::vec3(-radius,-radius, -radius), glm::vec3(0.0f, -1.0f, 0.0f)},
           {glm::vec3(-radius,-radius, radius),  glm::vec3(-0.0f, -1.0f, 0.0f)},
           {glm::vec3(radius,-radius, radius),   glm::vec3(-0.0f, -1.0f, 0.0f)},
           {glm::vec3(radius,-radius, -radius),  glm::vec3(-0.0f, -1.0f, 0.0f)},

           {glm::vec3(-radius,radius, -radius),  glm::vec3(0.0f, 1.0f, 0.0f)},
           {glm::vec3(radius,radius, -radius),   glm::vec3(0.0f, 1.0f, 0.0f)},
           {glm::vec3(radius,radius, radius),    glm::vec3(0.0f, 1.0f, 0.0f)},
           {glm::vec3(-radius,radius, radius),   glm::vec3(0.0f, 1.0f, 0.0f)},
      
        };
        return vertices;
    }

    std::vector<unsigned int> generIndices()
    {
        return { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
    }
    double radius;
};
#endif