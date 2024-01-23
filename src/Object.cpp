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
	IBO = 0;

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
	elements = 0;
}

Object::Object(std::vector<float> vertex, std::vector<unsigned int> indices, unsigned int stride)
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

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

	GLCall(glVertexAttribPointer(0, stride, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0));
	GLCall(glEnableVertexAttribArray(0));


	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GLCall(glBindVertexArray(0));


	elements = indices.size();
}

Object::Object(std::vector<float> vertex, std::vector<unsigned int> indices, glm::vec3 startPosition, unsigned int stride)
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

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

	GLCall(glVertexAttribPointer(0, stride, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0));
	GLCall(glEnableVertexAttribArray(0));


	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));


	model = glm::translate(model, position);
	this->size = vertex.size() / stride;

	elements = indices.size();
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
	elements = 0;
}

Object::~Object()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &IBO);
}

void Object::Draw()
{
	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
	GLCall(glBindVertexArray(0));
}

void Object::DrawElements()
{
		GLCall(glBindVertexArray(VAO));
		GLCall(glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0));
		GLCall(glBindVertexArray(0));
}
