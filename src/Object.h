#ifndef OBJECT_H
#define OBJECT_H

#include"shader.h"
#define SHADER_H

class Object
{
public:
	Object();
	Object(std::vector<float> vertex, unsigned int stride);
	Object(std::vector<float> vertex,std::vector<unsigned int> indices, unsigned int stride);
	Object(std::vector<float> vertex,std::vector<unsigned int> indices, glm::vec3 startPosition, unsigned int stride);
	Object(std::vector<float> vertex,glm::vec3 startPosition,unsigned int stride);
	~Object();


	//Functions
	void Draw();
	void DrawElements();


public:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
	unsigned int size;
	unsigned int elements;
	glm::vec3 position;
	glm::vec3 changePos;
	glm::mat4 model;
	bool obstacle;
};

#endif

