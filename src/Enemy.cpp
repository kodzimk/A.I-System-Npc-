#include "Enemy.h"

Enemy::Enemy()
{
	this->isChase = false;
	this->chasePos = { 0.0f,0.0f,0.0f };
	position = { 0.0f,0.0f,0.0f };
	scale = { 0.0f,0.0f,0.0f };
	model = glm::mat4(1.0f);
	actualPos = { 0.0f,0.0f,0.0f };
	obstacle = false;
	VBO = 0;
	VAO = 0;
	isCollisionEnable = true;
	direction = DIRECTION::IDLE;
	elements = 0;
}

Enemy::~Enemy()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &IBO);
}

void Enemy::DrawTriangle(unsigned int shader)
{
	GLCall(glBindVertexArray(this->VAO));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
	GLCall(glBindVertexArray(0));
}

void Enemy::DrawCirlce(unsigned int shader)
{
	GLCall(glBindVertexArray(VAO));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
	GLCall(glBindVertexArray(0));
}

void Enemy::DrawCube(unsigned int shader)
{
	GLCall(glBindVertexArray(VAO));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	GLCall(glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0));
	glBindVertexArray(0);
}

void Enemy::CreateCube(glm::vec3 scale)
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
	width = scale.x;
	height = scale.y;

	model = glm::scale(model, scale);
	isCollisionEnable = true;
}

void Enemy::CreateTriangle(glm::vec3 scale)
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

	width = scale.x;
	height = scale.y;

	model = glm::scale(model, scale);
	isCollisionEnable = true;
}

void Enemy::CreateCircle(float radius, int vCount, glm::vec3 scale)
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	size = vertices.size();
	width = radius * 2 * scale.x;
	height = radius * 2 * scale.y;

	model = glm::scale(model, scale);

	isCollisionEnable = true;
}

void Enemy::SetVisibilty(bool visibility)
{
	isCollisionEnable = visibility;
}

bool Enemy::isCollide(glm::vec3 position, float width, float height, bool Colision)
{
	if (Colision == true && isCollisionEnable == true)
	{
		glm::vec3 box1right = { this->actualPos.x,this->actualPos.y,this->actualPos.z };
		glm::vec3 box1Left = { this->actualPos.x + this->width,this->actualPos.y + this->height,this->actualPos.z };

		glm::vec3 box2right = { position.x,position.y,position.z };
		glm::vec3 box2Left = { width + position.x ,height + position.y ,position.z };

		if (box2right.x <= box1Left.x &&
			box2Left.x >= box1right.x &&
			box2right.y <= box1Left.y &&
			box2Left.y >= box1right.y)
		{
			return true;
		}
	}
	return false;
}

void Enemy::translate(float x, float y, float z)
{

	position.x = position.x + x;
	position.y = position.y + y;

	model = glm::translate(model, glm::vec3(x, y, z));
}

bool Enemy::isCollidePosition(glm::vec3 position, float width, float height)
{
	glm::vec3 box1right = { this->actualPos.x,this->actualPos.y,this->actualPos.z };
   	glm::vec3 box1Left = { this->actualPos.x + this->width,this->actualPos.y + this->height,this->actualPos.z };
   
   	glm::vec3 box2right = { position.x,position.y,position.z };
   	glm::vec3 box2Left = { width + position.x ,height + position.y ,position.z };
   
   	if (box2right.x <= box1Left.x &&
   		box2Left.x >= box1right.x &&
   		box2right.y <= box1Left.y &&
   		box2Left.y >= box1right.y)
   	{
   		return true;
   	}

   return false;
}

void Enemy::Chase(std::vector<glm::vec3> positions,glm::vec3 position,float width,float height,bool isCollide1)
{
	glm::vec3 actualpos2 = position;
	isChase = true;
	
	if(!isCollide(actualpos2,width,height,isCollide1))
	   isCanMove(positions,actualpos2, width, height, isCollide1);
}

void Enemy::isCanMove(std::vector<glm::vec3> positions,glm::vec3 position, float width, float height,bool isCollde)
{
	actualPos.x = this->position.x * this->width;
	actualPos.y = this->position.y * this->height;



	if (isChase)
	{
		if (direction == DIRECTION::IDLE)
		{
			bool isColliisionVolume = false;
			for (int i = 0; i < positions.size(); i++)
			{
				if (this->actualPos.y > position.y)
				{
					for (int k = 0; k < 100; k++)
					{

						if (isCollide(glm::vec3(positions[i].x, (positions[i].y + k * 0.05f) * height, positions[i].z), width, height, isCollde))
						{
							isColliisionVolume = true;
							k = 100;
						}
			
					}

					if (!isColliisionVolume)
					{
						direction = DIRECTION::DOWN;
						break;
					}

					isColliisionVolume = false;
				}
				else if (this->actualPos.y < position.y)
				{
					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3(positions[i].x, (positions[i].y - float(k) * 0.02f) * height, positions[i].z), width, height, isCollde))
						{
							isColliisionVolume = true;
							k = 100;

						}
	
					}

					if (!isColliisionVolume)
					{
						direction = DIRECTION::UP;
						break;
					}

					isColliisionVolume = false;
				}

				 if (this->actualPos.x < position.x)
				{
					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3((positions[i].x - k * 0.05f) * width, positions[i].y, positions[i].z), width, height, isCollde))
						{
							isColliisionVolume = true;
							k = 100;
						}

					}
					if (!isColliisionVolume)
					{
						direction = DIRECTION::RIGHT;
						break;
					}

					isColliisionVolume = false;
				}
				 else if (this->actualPos.x > position.x)
				 {
					for (int k = 0; k < 100; k++)
					{

						if (isCollide(glm::vec3((positions[i].x + k * 0.05f) * width, positions[i].y, positions[i].z), width, height, isCollde))
						{
							isColliisionVolume = true;
							k = 100;
						}
		
					}

					if (!isColliisionVolume)
					{
						direction = DIRECTION::LEFT;
						break;
					}
					isColliisionVolume = false;
				}				
			}
		}

	    if (direction == DIRECTION::LEFT)
		{

			if (!isCollide(position, width, height, isCollde))
				translate(-0.0005f, 0.0f, 0.0f);

			bool isCollideObject = false;
			bool isCollideVolume = false;

			for (int i = 0; i < positions.size(); i++) {

				if (this->actualPos.x < position.x)
				{
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3((position.x - float(j) * 0.05f) * width, position.y, position.z), width, height, isCollde))
						{
							isCollideObject = true;
							j = 100;
						}
					}
					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3((positions[i].x - float(k) * 0.05f) * width, positions[i].y, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
						}
						k = 100;
					}

					if (!isCollideVolume && isCollideObject)
					{
						direction = DIRECTION::RIGHT;
						break;
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
				if (this->actualPos.x > position.x)
				{
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3((position.x + float(j) * 0.05f) * width, position.y, position.z), width, height, isCollde))
						{
							isCollideObject = true;
						}

					}

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3((positions[i].x + float(k) * 0.05f) * width, positions[i].y, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
						}
					}

					if (!isCollideVolume && isCollideObject)
					{
						direction = DIRECTION::LEFT;
						break;
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
				if (this->actualPos.y > position.y)
				{
					for (int j = 0; j < 100; j++) {
						if (isCollide(glm::vec3(position.x - 0.5f, (position.y + float(j) * 0.05f) * height, position.z), width, height, isCollde)) {
							isCollideObject = true;
							j = 100;
						}
					}

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3(positions[i].x - 0.5f, (positions[i].y + float(k) * 0.05f) * height, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
							k = 100;
						}
					}

					if (isCollideVolume == false && isCollideObject == true)
					{
						direction = DIRECTION::DOWN;
						i = positions.size();
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
				if (this->actualPos.y < position.y) {
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3(position.x - 0.2f, (position.y - j * 0.05f) * height, position.z), width, height, isCollde))
						{
							isCollideObject = true;
							j = 100;

						}
					}

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3(positions[i].x-0.2f, (position.y - k * 0.05f) * height, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
							k = 100;
						}
					}

					if (!isCollideVolume && isCollideObject)
					{
						direction = DIRECTION::UP;
						break;
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
			}
		}

		if (direction == DIRECTION::UP)
		{
			if (!isCollide(position, width, height, isCollde))
				translate(0.0f, 0.0005f, 0.0f);


			bool isCollideObject = false;
			bool isCollideVolume = false;

			for (int i = 0; i < positions.size(); i++) {

				if (this->actualPos.x < position.x)
				{
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3((position.x - float(j) * 0.05f) * width, position.y, position.z), width, height, isCollde))
						{
							isCollideObject = true;
							j = 100;
						}
					}
					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3((positions[i].x - float(k) * 0.05f) * width, positions[i].y, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
						}
						k = 100;
					}

					if (!isCollideVolume && isCollideObject)
					{
						direction = DIRECTION::RIGHT;
						break;
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
				if (this->actualPos.x > position.x)
				{
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3((position.x + float(j) * 0.05f) * width, position.y, position.z), width, height, isCollde))
						{
							isCollideObject = true;
						}

					}

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3((positions[i].x + float(k) * 0.05f) * width, positions[i].y, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
						}
					}

					if (!isCollideVolume && isCollideObject)
					{
						direction = DIRECTION::LEFT;
						break;
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
				if (this->actualPos.y > position.y)
				{
					for (int j = 0; j < 100; j++) {
						if (isCollide(glm::vec3(position.x, (position.y + float(j) * 0.05f) * height, position.z), width, height, isCollde)) {
							isCollideObject = true;
							j = 100;
						}
					}

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3(positions[i].x, (positions[i].y + float(k) * 0.05f) * height, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
							k = 100;
						}
					}

					if (isCollideVolume == false && isCollideObject == true)
					{
						direction = DIRECTION::DOWN;
						i = positions.size();
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
				if (this->actualPos.y < position.y) {
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3(position.x, (position.y - j * 0.05f) * height, position.z), width, height, isCollde))
						{
							isCollideObject = true;
							j = 100;

						}
					}

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3(positions[i].x, (position.y - k * 0.05f) * height, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
							k = 100;
						}
					}

					if (!isCollideVolume && isCollideObject)
					{
						direction = DIRECTION::UP;
						break;
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
			}
		}

		if (direction == DIRECTION::DOWN)
		{
			if (!isCollide(position, width, height, isCollde))
				translate(0.0f, -0.0005f, 0.0f);

			bool isCollideObject = false;
			bool isCollideVolume = false;

			for (int i = 0; i < positions.size(); i++) {

				if (this->actualPos.x < position.x)
				{
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3((position.x - float(j) * 0.05f) * width, position.y, position.z), width, height, isCollde))
						{
							isCollideObject = true;
							j = 100;
						}
					}
					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3((positions[i].x - float(k) * 0.05f) * width, positions[i].y, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
						}
						k = 100;
					}

					if (!isCollideVolume && isCollideObject)
					{
						direction = DIRECTION::RIGHT;
						break;
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
				if (this->actualPos.x > position.x)
				{
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3((position.x + float(j) * 0.05f) * width, position.y, position.z), width, height, isCollde))
						{
							isCollideObject = true;
						}

					}

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3((positions[i].x + float(k) * 0.05f) * width, positions[i].y, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
						}
					}

					if (!isCollideVolume && isCollideObject)
					{
						direction = DIRECTION::LEFT;
						break;
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
				if (this->actualPos.y > position.y)
				{
					for (int j = 0; j < 100; j++) {
						if (isCollide(glm::vec3(position.x, (position.y + float(j) * 0.05f) * height, position.z), width, height, isCollde)) {
							isCollideObject = true;
							j = 100;
						}
					}

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3(positions[i].x, (positions[i].y + float(k) * 0.05f) * height, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
							k = 100;
						}
					}

					if (isCollideVolume == false && isCollideObject == true)
					{
						direction = DIRECTION::DOWN;
						i = positions.size();
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
				if (this->actualPos.y < position.y) {
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3(position.x, (position.y - j * 0.05f) * height, position.z), width, height, isCollde))
						{
							isCollideObject = true;
							j = 100;

						}
					}

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3(positions[i].x, (position.y - k * 0.05f) * height, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true;
							k = 100;
						}
					}

					if (!isCollideVolume && isCollideObject)
					{
						direction = DIRECTION::UP;
						break;
					}

					isCollideVolume = false;
					isCollideObject = false;
				}
			}

		}

		if (direction == DIRECTION::RIGHT)
		{
			if (!isCollide(position, width, height, isCollde))
				translate(0.0005f, 0.0f, 0.0f);


			bool isCollideObject = false;
			bool isCollideVolume = false;

			for (int i = 0; i < positions.size(); i++) {

				if (this->actualPos.x < position.x)
				{
					for (int j = 0; j < 100; j++) 
					{
						if (isCollide(glm::vec3((position.x - float(j) * 0.1f) * width, position.y, position.z), width, height, isCollde)) 
						{ 
							isCollideObject = true;
							j = 100;
						}
					} 
					for (int k = 0; k < 100; k++) 
					{ 
						if (isCollide(glm::vec3((positions[i].x - float(k) * 0.1f) * width, positions[i].y, positions[i].z), width, height, isCollde)) 
						{ 
							isCollideVolume = true;
						}
						k = 100;
					} 

					if (!isCollideVolume && isCollideObject)
					{ 
						direction = DIRECTION::RIGHT;
						break; 
					} 

					isCollideVolume = false; 
					isCollideObject = false;
				}
				if  (this->actualPos.x > position.x) 
				{
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3((position.x + float(j) * 0.1f) * width, position.y, position.z), width, height, isCollde))
						{ 
							isCollideObject = true;
						}

					} 

					for (int k = 0; k < 100; k++) 
					{ 
						if (isCollide(glm::vec3((positions[i].x + float(k) * 0.1f) * width, positions[i].y, positions[i].z), width, height, isCollde))
						{
							isCollideVolume = true; 
						} 
					}

					if (!isCollideVolume && isCollideObject)
					{ 
						direction = DIRECTION::LEFT;
						break;
					} 

					isCollideVolume = false; 
					isCollideObject = false;
				}
				if  (this->actualPos.y > position.y)
				{
					for (int j = 0; j < 100; j++) { 
						if (isCollide(glm::vec3(position.x, (position.y + float(j) * 0.1f) * height, position.z), width, height, isCollde)) {
							isCollideObject = true;
							j = 100;
						}
					} 

					for (int k = 0; k < 100; k++)
					{
						if (isCollide(glm::vec3(positions[i].x, (positions[i].y + float(k) * 0.1f) * height, positions[i].z), width, height, isCollde))
						{ 
							isCollideVolume = true; 
							k = 100;
						}
					}

					if (isCollideVolume == false && isCollideObject == true) 
					{
						direction = DIRECTION::DOWN;
						i = positions.size();
					} 

					isCollideVolume = false;
					isCollideObject = false;
				}
				if  (this->actualPos.y < position.y) {
					for (int j = 0; j < 100; j++)
					{
						if (isCollide(glm::vec3(position.x, (position.y - j * 0.1f) * height, position.z), width, height, isCollde))
						{
							isCollideObject = true;
							j = 100;

						}
					}

					for (int k = 0; k < 100; k++)
					{ 
						if (isCollide(glm::vec3(positions[i].x, (position.y - k * 0.1f) * height, positions[i].z), width, height, isCollde)) 
						{
							isCollideVolume = true;
							k = 100;
						} 
					} 

					if (!isCollideVolume && isCollideObject)
					{ 
						direction = DIRECTION::UP;
						break;
					}

					isCollideVolume = false; 
					isCollideObject = false;
				}
			}
		}
	}

		if (isCollide(position, width, height, isCollde))
		{
			isChase = false;
			direction = DIRECTION::IDLE;
			std::cout << "finish";
		}
	

}

