#include"Object.h"
#include"Shader.h"


#define OBJECT_H
#define SHADER_H

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
           0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    Object player(vertices, 3);

    Shader shader;


    while (!glfwWindowShouldClose(window))
    {
       
        glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        GLCall(glBindVertexArray(player.VAO));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, player.size));
        GLCall(glBindVertexArray(0));


        glfwSwapBuffers(window);

  
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}