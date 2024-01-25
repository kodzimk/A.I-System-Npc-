#include"shader.h"


class Object
{
public:
	Object();
	~Object();


	//Functions
	void DrawCube();
	void DrawTriangle();
	void DrawCirlce();
	void CreateCube();
	void CreateTriangle();
	void CreateCircle(float radius, int vCount);
	void SetVisibilty(bool visibilty);
	bool isCollide(Object object);


public:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
	unsigned int size;
	unsigned int elements;

	glm::vec3 position;
	glm::vec3 changePos;
	glm::mat4 model;
	int width;
	int height;
	bool obstacle;

private:
	float vertices[9] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	float vertex[12] = { 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f };
	unsigned int indices[6] = {
	  0, 1, 3,
	  1, 2, 3
	};

	bool isCollisionEnable;
};


