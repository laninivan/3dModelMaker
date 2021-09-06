#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

int g_windowSizeX = 640;
int g_windowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX=width;
    g_windowSizeY = height;
    glViewport(0, 0, width, height);
}

void glfwKeyCallback(GLFWwindow *pWindow, int key, int scancode, int action, int mode) 
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void)
{
    

    /* Initialize the library */
    if (!glfwInit())
    {
        cout << "glfwInit failed!" << endl;
        return -1;
    }

     

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "3dModelMaker", nullptr, NULL);
    if (!pWindow)
    {
        cout << "glfwCreateWindow failed!" << endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    glfwMakeContextCurrent(pWindow);
	
	if (!gladLoadGL())
	{
		cout << "Can't load GLAD" <<endl;
		return -1;
	}
	
    cout << "Renderer" << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: .*." << glGetString(GL_VERSION) << endl;
	
	glClearColor(1,1,0,1);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}