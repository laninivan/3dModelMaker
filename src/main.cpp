#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Windows.h>

#include <iostream>
#include <numeric>

#include "Camera/camera.h"
#include "Renderer/ShaderProgram.cpp"
#include "Object/LightSource.cpp"
#include "Object/Cube.cpp"
#include "Renderer/Mesh.cpp"
#include "Renderer/Model.cpp"
#include "Object/ModelManager.cpp"
#include "Events/EventsManager.cpp"
#include "AlgGeometric/AlgGeometric.h"
#include "Triangulation/List.h"
#include "Triangulation/Triangulation.cpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 3.0f, 0.0f));;
EventsManager eManager = EventsManager();
GLFWwindow* windowInit();
GLFWwindow* window = windowInit();
ModelManager manager(&camera);
int main()
{
   

   /* std::vector<glm::vec2> firstVector = {
        {0,-1},
        {1,1},
        {4,-2},
        {4,1},
        {6,4},
        {3,2},
        {2,1},
        {2,4},
        {-2,-1},
    };*/
    //std::vector<glm::vec2> firstVector = {
    //    {0,-2},
    //    {3,-4},
    //    {7,-2},
    //    {5,1},
    //    {3,-1},
    //    {2,2},
    //    {1,0},
    //    {0,2},
    //    {-1,3},
    //    {-3,0},
    //    {-4,-1},
    //    {-1,-3},
    //   /* {-1,-1},
    //    {1,-1},
    //    {1,1},
    //    {-1,1},*/
    //};
   
    //List list;
    //list.insert(firstVector);
    //std::vector<int>endIndexes = Triangulation::triangulationMonotone(&list);
    //for (int i = 0; i < endIndexes.size()-2; i+=3)
    //{
    //    std::cout << endIndexes[i] << " " << endIndexes[i+1] << " " << endIndexes[i+2] << std::endl;
    //}
    //std::cout << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;     
        processInput(window);
         
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        manager.drawAll(eManager);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    manager.deleteBufers();
    glfwTerminate();
    return 0;
}


GLFWwindow* windowInit()
{
    // glfw: инициализация и конфигурирование
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL for Ravesli.com", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetKeyCallback(window, key_callback);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        //return -1;
    }
    return window;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
     
  
    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_G && action == GLFW_PRESS)
    {
        if(eManager.typeOperation != TYPES_OPERATION(Translate))
            eManager.typeOperation = TYPES_OPERATION(Translate);
        else eManager.typeOperation = TYPES_OPERATION(Select);
        std::cout << "  typeOperation set: " << eManager.typeOperation << std::endl;
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        if (eManager.typeOperation != TYPES_OPERATION(Rotation))
            eManager.typeOperation = TYPES_OPERATION(Rotation);
        else eManager.typeOperation = TYPES_OPERATION(Select);
        std::cout << "  typeOperation set: " << eManager.typeOperation << std::endl;
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        if (eManager.typeOperation != TYPES_OPERATION(Scale))
            eManager.typeOperation = TYPES_OPERATION(Scale);
        else eManager.typeOperation = TYPES_OPERATION(Select);
        std::cout << "  typeOperation set: " << eManager.typeOperation << std::endl;
    }
    if (key == GLFW_KEY_INSERT && action == GLFW_PRESS)
    {
        if (eManager.typeOperation != TYPES_OPERATION(Create))
            eManager.typeOperation = TYPES_OPERATION(Create);
        else eManager.typeOperation = TYPES_OPERATION(Select);
        std::cout << "  typeOperation set: " << eManager.typeOperation << std::endl;
    }
    if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Select))
            manager.addIntermediateVertexes();
        
    }


    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Translate))
        {        
            manager.translate(glm::vec3(-0.05f,0.0f,0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Rotation))
        {
            manager.rotate(glm::vec3(-0.0436f, 0.0f, 0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Scale))
        {
            manager.scaleAdd(glm::vec3(-0.1f, 0.0f, 0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Select))
        {
            manager.selectPrev();
        }
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Translate))
        {
            manager.translate(glm::vec3(0.05f, 0.0f, 0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Rotation))
        {
            manager.rotate(glm::vec3(0.0436, 0.0f, 0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Scale))
        {
            manager.scaleAdd(glm::vec3(0.1f, 0.0f, 0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Select))
        {
            manager.selectNext();
        }
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Translate))
        {
            manager.translate(glm::vec3(0.0f, 0.05f, 0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Rotation))
        {
            manager.rotate(glm::vec3(0.0f, 0.0436, 0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Scale))
        {
            manager.scaleAdd(glm::vec3(0.0f, 0.1f, 0.0f));
        }
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Translate))
        {
            manager.translate(glm::vec3(0.0f, -0.05f, 0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Rotation))
        {
            manager.rotate(glm::vec3(0.0f, -0.0436, 0.0f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Scale))
        {
            manager.scaleAdd(glm::vec3(0.0f, -0.1f, 0.0f));
        }
    }
    if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Translate))
        {
            manager.translate(glm::vec3(0.0f, 0.0f, -0.1f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Rotation))
        {
            manager.rotate(glm::vec3(0.0f, 0.0f, -0.0436));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Scale))
        {
            manager.scaleAdd(glm::vec3(0.0f, 0.0f, -0.1f));
        }
    }
    if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Translate))
        {
            manager.translate(glm::vec3(0.0f, 0.0f, 0.1f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Rotation))
        {
            manager.rotate(glm::vec3(0.0f, 0.0f, 0.1f));
        }
        if (eManager.typeOperation == TYPES_OPERATION(Scale))
        {
            manager.scaleAdd(glm::vec3(0.0f, 0.0f, 0.1f));
        }
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
            eManager.typeObject = TYPES_OBJECT(Models);
            std::cout << "  mode objects: " << eManager.typeObject << std::endl;
            manager.setIndexCurFace(-1);
            manager.setIndexCurMesh(-1);
            manager.setIndexCurVertex(-1);
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
            eManager.typeObject = TYPES_OBJECT(Meshes);
            std::cout << "  mode objects: " << eManager.typeObject << std::endl;
            manager.setIndexCurFace(-1);
            manager.setIndexCurVertex(-1);
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        eManager.typeObject = TYPES_OBJECT(Faces);
        std::cout << "  mode objects: " << eManager.typeObject << std::endl;
        manager.setIndexCurVertex(-1);
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        eManager.typeObject = TYPES_OBJECT(Edges);
        std::cout << "  mode objects: " << eManager.typeObject << std::endl;
        manager.setIndexCurVertex(-1);
    }
    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        eManager.typeObject = TYPES_OBJECT(Vertexes);
        std::cout << "  mode objects: " << eManager.typeObject << std::endl;
        manager.setIndexCurVertex(0);
    }
    if (key ==GLFW_KEY_DELETE && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Select))
        {
            manager.deleteSelected();
        }       
    }
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Select))
        {
            manager.triangulate();
        }
    }
    if ((key == GLFW_KEY_KP_ADD && action == GLFW_PRESS))
    {
        if (eManager.typeOperation == TYPES_OPERATION(Select))
        {
            manager.copy();
        }
    }
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // перевернуто, так как y-координаты идут снизу вверх

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (eManager.typeOperation == TYPES_OPERATION(Select))
        {

                manager.setSelectMode(true);
                manager.drawAll(eManager);
                glm::vec3 color;
                glReadPixels(SCR_WIDTH / 2, SCR_HEIGHT / 2, 1, 1, GL_RGB, GL_FLOAT, &color);
                if (eManager.typeObject == TYPES_OBJECT(Models))
                {
                    manager.setIndexCurModel(round(color[0] * 100) - 1);
                }
                if (eManager.typeObject == TYPES_OBJECT(Meshes))
                {
                    manager.setIndexCurMesh(round(color[1] * 100) - 1);
                }
                manager.setSelectMode(false);
                if (eManager.typeObject == TYPES_OBJECT(Faces))
                {                 
                    manager.selectFace();
                }   
                
                std::cout << "SELECT MODEL: " << manager.getIndexCurModel() << std::endl;
                std::cout << "SELECT MESH : " << manager.getIndexCurMesh() << std::endl;
                std::cout <<"SELECT FACE: " << manager.getIndexCurFace() << std::endl;                             
                std::cout <<"SELECT Vertex: " << manager.getIndexCurVertex() << std::endl;                             
        }
             
        if (eManager.typeOperation == TYPES_OPERATION(Translate))
        {
            manager.setLocation(AlgGeometric::getPointPlaneAndVector(glm::vec3 (0,0,0), glm::vec3(0,0,1),camera.Position, camera.Front));
        }

        if (eManager.typeOperation == TYPES_OPERATION(Create))
        {
            glm::vec3 posObject = AlgGeometric::getPointPlaneAndVector(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), camera.Position, camera.Front);
            if (eManager.typeObject == TYPES_OPERATION(CubeCreating))
            {
                Cube tempCupe = Cube(1.0f, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0.f, 0.0f, 0.0f);
                    Model tempModel({ tempCupe }, glm::vec3(0.5f, 0.5f, 0.4f), glm::vec3(0.8f, 0.8f, 0.9f), posObject, glm::vec3(1, 1, 1), 0.f, 0.f, 0.f, GL_TRIANGLE_FAN);
                    manager.addModel(tempModel);
            }
        }
    }    
}



void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

