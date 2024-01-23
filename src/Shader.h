#ifndef SHADER_H
#define SHADER_H

#include"config.h"

class Shader
{
public:
	Shader();
	~Shader();

	//Functions
	void use();

public:
	unsigned int program;
};

#endif

