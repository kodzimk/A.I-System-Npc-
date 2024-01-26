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
    object.translate(-0.5f, 0.0f, 0.0f);
    
    Object player;
    player.CreateCube(glm::vec3(0.3f,1.f,1.0f));
    player.translate(0.4f, 0.0f, 0.0f);

    
    Enemy enemy;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       
        shader.use();
        glBindVertexArray(object.VAO);
        object.DrawCube(shader.program);
        glBindVertexArray(player.VAO);
        player.DrawCube(shader.program);

        std::cout << object.isCollide(player.position,player.width,player.height,player.isCollisionEnable)<<std::endl;

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

