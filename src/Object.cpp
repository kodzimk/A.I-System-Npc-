#include "Object.h"

Object::Object()
{
	position = { 0.0f,0.0f,0.0f };
	changePos = { 0.0f,0.0f,0.0f };
	model = glm::mat4(1.0f);
	obstacle = false;
	VBO = 0;
	VAO = 0;
}

Object::Object(std::vector<float> vertex, unsigned int stride)
{
	position = { 0.0f,0.0f,0.0f };
	changePos = { 0.0f,0.0f,0.0f };
	model = glm::mat4(1.0f);
	obstacle = false;

	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glBindVertexArray(VAO));

	GLCall(glGenBuffers(1, &VBO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex.data(), GL_STATIC_DRAW));
	

	GLCall(glVertexAttribPointer(0, stride, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	this->size = vertex.size() / stride;
}

Object::Object(std::vector<float> vertex, glm::vec3 startPosition,unsigned int stride)
{
	position = startPosition;
	changePos = { 0.0f,0.0f,0.0f };
	model = glm::mat4(1.0f);
	obstacle = false;

	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glBindVertexArray(VAO));

	GLCall(glGenBuffers(1, &VBO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex.data(), GL_STATIC_DRAW));


	GLCall(glVertexAttribPointer(0, stride, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	model = glm::translate(model, position);
	this->size = vertex.size() / stride;
}

Object::~Object()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Object::Draw()
{
	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
	GLCall(glBindVertexArray(0));
}
