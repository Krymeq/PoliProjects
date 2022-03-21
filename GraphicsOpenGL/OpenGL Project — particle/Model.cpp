#include "Model.h"

Model::Model()
{
	transformMatrix = glm::mat4(1.0f);
}

Model::Model(std::string dataFile, std::string textureFile)
{
	this->loadFromFile(dataFile);
	this->loadTexture(textureFile);
	transformMatrix = glm::mat4(1.0f);
}

Model::Model(Model* src)
{
	this->copyDataFromAnotherModel(src);
}

Model::~Model()
{
	
}

void Model::draw(ShaderProgram* sp, glm::mat4 v, glm::mat4 p, glm::mat4 m)
{
	sp->use();

	glm::mat4 model = m * this->transformMatrix;
	glBindTexture(GL_TEXTURE_2D, this->texture);

	glUniform3fv(sp->u("viewPosition"), 1, glm::value_ptr(cameraPosition));
	glUniformMatrix4fv(sp->u("model"), 1, false, glm::value_ptr(model));
	glUniformMatrix4fv(sp->u("view"), 1, false, glm::value_ptr(v));
	glUniformMatrix4fv(sp->u("projection"), 1, false, glm::value_ptr(p));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//printf("Vertices data: %d, texCoords: %d, normals: %d\n", this->vertices.size(), this->texCoords.size(), this->normals.size());

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, this->vertices.data());
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, this->normals.data());
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, this->texCoords.data());

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 4);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

//k¹t w stopniach!!
void Model::rotate(float angle, glm::vec3 axis) 
{
	transformMatrix = glm::rotate(transformMatrix, glm::radians(angle), axis);
}

void Model::translate(glm::vec3 vector)
{
	transformMatrix = glm::translate(transformMatrix, vector);
}

void Model::scale(glm::vec3 scalingFactor)
{
	transformMatrix = glm::scale(transformMatrix, scalingFactor);
}

void Model::loadFromFile(std::string path)
{
	std::string xd;
	std::fstream file;

	file.open(path, std::ios::in);

	if (file.good())
	{
		std::vector<glm::vec3> tempNormals;
		std::vector<glm::vec3> tempVertices;
		std::vector<glm::vec2> tempTexCoords;
		std::vector<int> vertexIndices, normalIndices, textureIndices;

		try
		{	
			// Read file data to temporary variables
			while (std::getline(file, xd))
			{
				// Temporary container to store read floats;
				std::vector<float> tabf = findAllFloatNumbers(xd);

				if (xd[0] == 'v' && xd[1] == 't')
				{
					glm::vec2 temp = glm::vec2(tabf[0], tabf[1]);
					tempTexCoords.push_back(temp);
				}

				else if (xd[0] == 'v' && xd[1] == 'n')
				{	
					glm::vec3 temp = glm::vec3(tabf[0], tabf[1], tabf[2]);
					tempNormals.push_back(temp);
				}

				else if (xd[0] == 'v')
				{
					glm::vec3 temp = glm::vec3(tabf[0], tabf[1], tabf[2]);
					tempVertices.push_back(temp);
				}

				else if (xd[0] == 'f')
				{
					for (int i = 0; i < tabf.size(); i++)
					{
						if (i % 3 == 0)
							vertexIndices.push_back(tabf[i]);
						else if (i % 3 == 1)
							textureIndices.push_back(tabf[i]);
						else if (i % 3 == 2)
							normalIndices.push_back(tabf[i]);
					}
				}
			}
			
			// transforming everything to proper model-class field
			if (!vertexIndices.empty())
			{
				for (int i = 0; i < vertexIndices.size(); i++)
				{
					try
					{
						this->vertices.push_back(tempVertices.at(vertexIndices.at(i) - 1).x);
						this->vertices.push_back(tempVertices.at(vertexIndices.at(i) - 1).y);
						this->vertices.push_back(tempVertices.at(vertexIndices.at(i) - 1).z);
						this->vertices.push_back(1.0f);

						this->normals.push_back(tempNormals.at(normalIndices.at(i) - 1).x);
						this->normals.push_back(tempNormals.at(normalIndices.at(i) - 1).y);
						this->normals.push_back(tempNormals.at(normalIndices.at(i) - 1).z);

						this->texCoords.push_back(tempTexCoords.at(textureIndices.at(i) - 1).x);
						this->texCoords.push_back(tempTexCoords.at(textureIndices.at(i) - 1).y);
					}
					catch (const std::out_of_range &e)
					{
						std::cout << "Filename: " + path << std::endl;
						printf("\nCurrent loop iteration: %d\n", i);
						printf("tempVertices size: %d, indication: %d\n", tempVertices.size(), vertexIndices[i] - 1);
						printf("tempNormals size: %d, indication: %d\n", tempNormals.size(), normalIndices[i] - 1);
						printf("tempTexCoords size: %d, indication: %d\n", tempTexCoords.size(), textureIndices[i] - 1);
						system("pause");
						exit(2137);
					}
				}
			}

			else
			{
				for (int i = 0; i < tempVertices.size(); i++)
				{
					this->vertices.push_back(tempVertices[i].x);
					this->vertices.push_back(tempVertices[i].y);
					this->vertices.push_back(tempVertices[i].z);
					this->vertices.push_back(1.0f);
				}

				for (int i = 0; i < tempNormals.size(); i++)
				{
					this->normals.push_back(tempNormals[i].x);
					this->normals.push_back(tempNormals[i].y);
					this->normals.push_back(tempNormals[i].z);
				}

				for (int i = 0; i < tempTexCoords.size(); i++)
				{
					this->texCoords.push_back(tempTexCoords[i].x);
					this->texCoords.push_back(tempTexCoords[i].y);
				}
			}
		}
		catch (...)
		{
			std::cout << "Parser encountered a problem. The program will now close" << std::endl;
		}
	}
	else std::cout << "Can't properly load model\n";

	file.close();
}

void Model::loadTexture(std::string path)
{
	std::vector<unsigned char> texData;

	unsigned int width, height;
	unsigned int error = lodepng::decode(texData, width, height, path);
	
	glGenTextures(1, &(this->texture));
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData.data());

	glGenerateMipmap(GL_TEXTURE_2D);
}

void Model::copyDataFromAnotherModel(Model* src)
{
	this->vertices = src->getVertexData();
	this->texCoords = src->getTexCoordData();
	this->normals = src->getNormalsData();
	this->transformMatrix = glm::mat4(1.0f);
}

std::vector<float> findAllFloatNumbers(std::string text)
{
	std::vector<float> res;
	std::string buffer;

	int start;
	bool copying = false;

	for (int i = 0; i < text.size() + 1; i++)
	{
		if (!copying)
		{
			if((text[i] >= '0' && text[i] <= '9') || text[i] == '-')
			{
				copying = true;
				start = i;
			}
		}

		else if ((text[i] < '0' || text[i] > '9') && text[i] != '.')
		{
			copying = false;
			buffer = text.substr(start, i - 1);
			try
			{
				res.push_back(std::stof(buffer));
			}
			catch (...)
			{
				std::cout << "Can't parse vertex data" << std::endl;
			}
		}
	}
	return res;
}

void Model::setTransformMatrix(glm::mat4 newMatrix)
{
	this->transformMatrix = newMatrix;
}

void Model::setNormals(std::vector<float> normalsData)
{
	this->normals = normalsData;
}

void Model::setTexCoords(std::vector<float> texCoordsData)
{
	this->texCoords = texCoordsData;
}

void Model::setVertices(std::vector<float> vertexData)
{
	this->vertices = vertexData;
}

std::vector<float> Model::getNormalsData()
{
	return this->normals;
}

std::vector<float> Model::getTexCoordData()
{
	return this->texCoords;
}

std::vector<float> Model::getVertexData()
{
	return this->vertices;
}

glm::mat4 Model::getTransformMatrix()
{
	return this->transformMatrix;
}