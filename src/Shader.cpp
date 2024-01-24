#include "Shader.h"

Shader::Shader()
{
    ShaderProgramSource src = ParseShaders("src/Shader/vertex_shader.vert", "src/Shader/fragment_shader.frag");



    const GLchar* vertexShaderSource = src.VertexSource.c_str();
    const GLchar* fragmentShaderSource = src.FragmentSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::use()
{
    glUseProgram(program);
}
