#include"Object.h"
#define OBJECT_H

int main(void)
{
    GLFWwindow* window;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
    if (!glfwInit())
        return -1;

   
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
  
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        return -1;

    std::vector<float> vertices = {
 0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f
    };


    std::vector<unsigned int> indices = {
        0, 1, 3,   // first triangle
    1, 2, 3
    };

    Object player(vertices,indices, 3);

    Shader shader;

    shader.use();

    while (!glfwWindowShouldClose(window))
    {     
        glClear(GL_COLOR_BUFFER_BIT);

       
        player.DrawElements();

        glfwSwapBuffers(window);
  
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}