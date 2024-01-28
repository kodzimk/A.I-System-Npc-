#include"shader.h"


class Object
{
public:
	Object();
	~Object();


	//Functions
	void DrawCube(unsigned int shader);
	void DrawTriangle(unsigned int shader);
	void DrawCirlce(unsigned int shader);
	void CreateCube(glm::vec3 scale);
	void CreateTriangle(glm::vec3 scale);
	void CreateCircle(float radius, int vCount, glm::vec3 scale);
	void SetVisibilty(bool visibilty);
	bool isCollide(glm::vec3 position, float width, float height,bool collide);

	void translate(float x, float y, float z);


public:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
	unsigned int size;
	unsigned int elements;

	glm::vec3 position;
	glm::mat4 model;
	glm::vec3 scale;
	glm::vec3 actualPos;
	float width;
	float height;
	bool obstacle;
	bool isCollisionEnable;


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


};


