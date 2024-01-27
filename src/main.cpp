#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include"Object.h"
#include"Enemy.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit()!=GLEW_OK)
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader;


    Object object;
    object.CreateCube(glm::vec3(0.5f, 0.5f, 1.0f));
    object.translate(-1.3f, 0.0f, 0.0f);
    
    Enemy enemy;
    enemy.CreateCube(glm::vec3(0.5f, 0.5f, 1.0f));
    enemy.translate(-1.3f, -1.3f, 0.0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       
        shader.use();
        glBindVertexArray(object.VAO);
        object.DrawCube(shader.program);
        glBindVertexArray(enemy.VAO);
        enemy.DrawCube(shader.program);

        enemy.Chase(object.position, object.width, object.height,object.isCollisionEnable);
       

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

