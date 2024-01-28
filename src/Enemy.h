#include"config.h"

enum DIRECTION {
	IDLE = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};

class Enemy 
{

public:
    Enemy();
    ~Enemy();

	void DrawCube(unsigned int shader);
	void DrawTriangle(unsigned int shader);
	void DrawCirlce(unsigned int shader);
	void CreateCube(glm::vec3 scale);
	void CreateTriangle(glm::vec3 scale);
	void CreateCircle(float radius, int vCount, glm::vec3 scale);
	void SetVisibilty(bool visibilty);
	bool isCollide(glm::vec3 position, float width, float height, bool collide);
	void translate(float x, float y, float z);
	bool isCollidePosition(glm::vec3 position, float width, float height);
	void SetTimer(double timer);
	void Wait();
	void Chase(std::vector<glm::vec3> positions, std::vector<float> widths, 
		std::vector<float> heights,
		std::vector<bool> collisions,
		glm::vec3 position, float width, float height,bool isCollide);
	void isCanMove(std::vector<glm::vec3> positions, std::vector<float> widths,
		std::vector<float> heights,
		std::vector<bool> collisions,
		glm::vec3 position, float width, float height,bool isCollide);


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

	bool isChase;
	glm::vec3 chasePos;

	DIRECTION direction;
	double timer;
	double EndTimer;
	bool startTimer;

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

