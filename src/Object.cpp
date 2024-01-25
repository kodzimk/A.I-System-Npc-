#include "Object.h"

Object::Object()
{
	position = { 0.0f,0.0f,0.0f };
	changePos = { 0.0f,0.0f,0.0f };
	scale = { 0.0f,0.0f,0.0f };
	model = glm::mat4(1.0f);
	obstacle = false;
	VBO = 0;
	VAO = 0;
	isCollisionEnable = true;

	elements = 0;
}

Object::~Object()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &IBO);
}

void Object::DrawTriangle(unsigned int shader)
{
	GLCall(glBindVertexArray(this->VAO));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
	GLCall(glBindVertexArray(0));
}

void Object::DrawCirlce(unsigned int shader)
{
	GLCall(glBindVertexArray(VAO));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
	GLCall(glBindVertexArray(0));
}

void Object::DrawCube(unsigned int shader)
{
		GLCall(glBindVertexArray(VAO));
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		GLCall(glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0));
		glBindVertexArray(0);
}

void Object::CreateCube(glm::vec3 scale)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	elements = 6;
	size = 0;
	width =  scale.x;
	height =  scale.y;

	model = glm::scale(model, scale);
}

void Object::CreateTriangle(glm::vec3 scale)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	elements = 0;
	size = 3;

	width =  scale.x;
	height = scale.y;

	model = glm::scale(model, scale);
}

void Object::CreateCircle(float radius,int vCount, glm::vec3 scale)
{
	std::vector<glm::vec3>vertices;
	float angle = 360.0f / vCount;

	int triangleCount = vCount - 2;

	std::vector<glm::vec3> temp;
	// positions
	for (int i = 0; i < vCount; i++)
	{
		float currentAngle = angle * i;
		float x = radius * cos(glm::radians(currentAngle));
		float y = radius * sin(glm::radians(currentAngle));
		float z = 0.0f;

		temp.push_back(glm::vec3(x, y, z));
	}
	// triangles
	for (int i = 0; i < triangleCount; i++)
	{
		vertices.push_back(temp[0]);
		vertices.push_back(temp[i + 1]);
		vertices.push_back(temp[i + 2]);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	size = vertices.size();
	width = radius* scale.x;
	height = radius* scale.y;

	model = glm::scale(model, scale);
}

void Object::SetVisibilty(bool visibility)
{
	isCollisionEnable = visibility;
}

bool Object::isCollide(glm::vec3 position,float width,float height)
{
	actualPos.x = position.x * this->width;
	actualPos.y = position.y * this->height;

	glm::vec3 box1right;
	glm::vec3 box1Left;

	glm::vec3 box2right;
	glm::vec3 box2Left;

	box1right.x = this->actualPos.x;
	box1right.y = this->actualPos.y;

	box1Left.x = this->actualPos.x + this->width;
	box1Left.y = this->actualPos.y + this->height;

	box2right.x = position.x;
	box2right.y = position.y;

	box2Left.x = width + position.x;
	box2Left.y = height + position.y;

	if (box2right.x <= box1Left.x &&
		box2Left.x >= box1right.x &&
		box2right.y <= box1Left.y &&
		box2Left.y >= box1right.y)
	{
		return true;
	}

	return false;
}

void Object::translate(float x, float y, float z)
{
	position.x =position.x + x;
	position.y =position.y + y;

	position.x = position.x * width;
	position.y = position.y * height;

	model = glm::translate(model, glm::vec3(x,y,z));
}

