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
    object.translate(1.3f, -1.3f, 0.0f);
    object.SetVisibilty(true);

    Object object1;
    object1.CreateCube(glm::vec3(0.5f, 0.5f, 1.0f));
    object1.translate(0.0f, 1.4f, 0.0f);
    object1.SetVisibilty(true);

    Object object2;
    object2.CreateCube(glm::vec3(0.2f, 0.2f, 1.0f));
    object2.translate(-0.4f, -1.0f, 0.0f);
    object2.SetVisibilty(true);
    
    
    Enemy enemy;
    enemy.CreateCube(glm::vec3(0.5f, 0.5f, 1.0f));
    enemy.translate(-1.3f, 1.3f, 0.0);

    std::vector<glm::vec3>positions;
    positions.push_back(object1.actualPos);

    std::vector<float>widths;
    widths.push_back(object1.width);

    std::vector<float>heights;
    heights.push_back(object1.height);

    std::vector<bool>collsions;
    collsions.push_back(object1.isCollisionEnable);

    positions.push_back(object2.actualPos);
    widths.push_back(object2.width);
    heights.push_back(object2.height);
    collsions.push_back(object2.isCollisionEnable);

    enemy.SetTimer(5.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       
        shader.use();
        glBindVertexArray(object.VAO);
        object.DrawCube(shader.program);
        glBindVertexArray(enemy.VAO);
        enemy.DrawCube(shader.program);
        glBindVertexArray(object1.VAO);
        object1.DrawCube(shader.program);

        glBindVertexArray(object2.VAO);
        object2.DrawCube(shader.program);
    
        enemy.Wait();
        enemy.Chase(positions,widths,heights,collsions, 
                   object.actualPos, object.width, object.height,
                   object.isCollisionEnable);

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

