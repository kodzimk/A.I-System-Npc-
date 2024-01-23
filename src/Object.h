#ifndef OBJECT_H
#define OBJECT_H

#include"config.h"

class Object
{
public:
	Object();
	Object(std::vector<float> vertex, unsigned int stride);
	Object(std::vector<float> vertex,glm::vec3 startPosition,unsigned int stride);
	~Object();


	//Functions
	void Draw();


public:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int size;
	glm::vec3 position;
	glm::vec3 changePos;
	glm::mat4 model;
	bool obstacle;
};

#endif

