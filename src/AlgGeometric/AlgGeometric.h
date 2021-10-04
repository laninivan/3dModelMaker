#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Camera/camera.h"

#ifndef ALG
#define ALG

class AlgGeometric
{
public:
	 static glm::vec3 getPointPlaneAndVector(glm::vec3 K, glm::vec3 N, glm::vec3 cameraPos, glm::vec3 cameraFront)
     {
        double t = (N.x * (K.x - cameraPos.x) + N.y * (K.y - cameraPos.y) + N.z * (K.z - cameraPos.z)) /
            (cameraFront.x * N.x + cameraFront.y * N.y + cameraFront.z * N.z);
        glm::vec3 result = glm::vec3(t * cameraFront.x + cameraPos.x, t * cameraFront.y + cameraPos.y, t * cameraFront.z + cameraPos.z);
        if (N.x * (cameraPos.x - K.x) + N.y * (cameraPos.y - K.y) + N.z * (cameraPos.z - K.z) < 0)
            return glm::vec3(10000, 10000, 10000);
        else return result; 
     }

     static double getSquareTriangle(glm::vec3 A, glm::vec3 B, glm::vec3 C)
     {
         glm::vec3 AB = B - A;
         glm::vec3 AC = C - A;
         glm::vec3 res = glm::cross(AB,AC);//AB*AC
         
         return 0.5f * sqrt(res.x*res.x+ res.y * res.y+ res.z * res.z);//glm:length
     }

     static double getDinst(glm::vec3 a, glm::vec3 b)
     {
         return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
     }

     static bool VertexBelongsToPolygon(Mesh mesh,int indexFace, glm::vec3 vertex)
     {
         Face face = mesh.indFaces[indexFace];
         double minDinst = 100000;
         int minDinstIndex = 100000;
         for (int i = 0; i < face.indexes.size(); i++)
         {
             double tempDinst = getDinst(vertex, mesh.vertices[face.indexes[i]].position);
                 if (tempDinst < minDinst)
                 {
                     minDinst = tempDinst;
                     minDinstIndex = i;
                 }
         }
         int prefIndex;
         int nextIndex;
         if (minDinstIndex ==0)
         {
             prefIndex = face.indexes.size()-1;
             nextIndex = 1;
         }
         else if (minDinstIndex == face.indexes.size()-1)
         {
             prefIndex = minDinstIndex-1;
             nextIndex = 0;
         }
         else
         {
             prefIndex = minDinstIndex - 1;
             nextIndex = minDinstIndex + 1;
         } 
         glm::vec3 v1 = mesh.vertices[face.indexes[prefIndex]].position;
         glm::vec3 v2 = mesh.vertices[face.indexes[minDinstIndex]].position;
         glm::vec3 v3 = mesh.vertices[face.indexes[nextIndex]].position;
         glm::vec3 delta = vertex - v2;
         vertex = glm::vec3(v2.x + (delta.x * 0.001f), v2.y + (delta.y * 0.001f), v2.z + (delta.z * 0.001f)  );//v2+delta*0.001
         double s1 = getSquareTriangle(v1, v2, vertex);
         double s2 = getSquareTriangle(v3, v2, vertex);
         double s3 = getSquareTriangle(v1, v3, vertex);
         double s4 = getSquareTriangle(v1, v2, v3);         
         if (s4 / (s1 + s2 + s3) >=0.99999f && s4 / (s1 + s2 + s3) <= 1.00001f)     
             return true;          
         else return false;
     }

     static glm::vec3 getPointFaceAndVector(Mesh mesh, int indexFace, Camera* camera,glm::mat4 modelMatrix)
     {
         modelMatrix = glm::translate(modelMatrix, mesh.getTranslate());
         modelMatrix = glm::scale(modelMatrix, mesh.getScale());
         modelMatrix = glm::rotate(modelMatrix, mesh.getRotAngleX(),glm::vec3(1.0f,0.0f,0.0f));
         modelMatrix = glm::rotate(modelMatrix, mesh.getRotAngleY(), glm::vec3(0.0f,1.0f,0.0f));
         modelMatrix = glm::rotate(modelMatrix, mesh.getRotAngleZ(), glm::vec3(0.0f,0.0f,1.0f));
         modelMatrix = glm::inverse(modelMatrix);
         glm::vec3 endPointVector = (*camera).Position + (*camera).Front;
         endPointVector= glm::vec3(modelMatrix * glm::vec4(endPointVector, 1.0));

         Face face = mesh.indFaces[indexFace];
         glm::vec3 normal = mesh.vertices[face.indexes[0]].normal;
         glm::vec3 pointPlanes = mesh.vertices[face.indexes[0]].position;      
         glm::vec3 cameraPos = glm::vec3(modelMatrix * glm::vec4((*camera).Position, 1.0));
         glm::vec3 cameraFront = endPointVector - cameraPos;
         glm::vec3 result = getPointPlaneAndVector(pointPlanes, normal, cameraPos, cameraFront);

        // if (result == glm::vec3(10000, 10000, 10000))
             //return result;
         
         if (!VertexBelongsToPolygon(mesh, indexFace, result))
             return glm::vec3(10000, 10000, 10000);
         return result;
             
     }




};

#endif