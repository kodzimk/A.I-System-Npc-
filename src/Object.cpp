#include "Object.h"

Object::Object()
{
	position = { 0.0f,0.0f,0.0f };
	changePos = { 0.0f,0.0f,0.0f };
	model = glm::mat4(1.0f);
	obstacle = false;
	VBO = 0;
	VAO = 0;




	elements = 0;
}


Object::~Object()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &IBO);
}

void Object::DrawTriangle()
{
	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
	GLCall(glBindVertexArray(0));
}

void Object::DrawCirlce()
{
	GLCall(glBindVertexArray(VAO));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
	GLCall(glBindVertexArray(0));
}

void Object::DrawCube()
{
		GLCall(glBindVertexArray(VAO));
		GLCall(glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0));
		glBindVertexArray(0);
}

void Object::CreateCube()
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
}

void Object::CreateTriangle()
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
}

void Object::CreateCircle(float radius,int vCount)
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
}


