#include"config.h"

int main(void)
{
    GLFWwindow* window;

  
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

    while (!glfwWindowShouldClose(window))
    {
       
        glClearColor(0.3f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(window);

  
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}