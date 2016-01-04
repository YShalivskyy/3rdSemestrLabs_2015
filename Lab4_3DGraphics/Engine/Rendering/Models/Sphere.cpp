#include "Sphere.h"
using namespace Engine::Rendering::Models;
using namespace Engine::Rendering;
Sphere::Sphere() :
	Sphere(glm::vec3(0.0, 0.0, 0.0), DEFAULT_SPHERE_VERTEX_COUNT, DEFAULT_SPHERE_RADIUS)
{
}

Sphere::Sphere(float r):
	Sphere(glm::vec3(0.0, 0.0, 0.0), DEFAULT_SPHERE_VERTEX_COUNT, r)
{
}

Sphere::Sphere(glm::vec3 pos) :
	Sphere(pos, DEFAULT_SPHERE_VERTEX_COUNT, DEFAULT_SPHERE_RADIUS)
{
}

Sphere::Sphere(glm::vec3 pos, float r) :
	Sphere(pos, DEFAULT_SPHERE_VERTEX_COUNT, r)
{
}

Sphere::Sphere(glm::vec3 pos, unsigned int count, float r):
	radius(r), vertexCount(count)
{
	position = pos;
}

Sphere::~Sphere()
{
}

void Sphere::create()
{
	GLuint vao;
	GLuint vbo;
	//GLuint ibo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	std::vector<VertexFormat> vertices;

	for (unsigned int iCounter = 0; iCounter < 360; iCounter += 360 / vertexCount)
	{
		for (unsigned int jCounter = 0; jCounter < 360; jCounter += 360 / vertexCount)
		{
			vertices.push_back(VertexFormat(
				glm::vec3(sin(iCounter * M_PI / 180) * radius,
					cos(iCounter * M_PI / 180) *sin(jCounter * M_PI / 180) * radius,
					cos(iCounter * M_PI / 180) * cos(jCounter * M_PI / 180) * radius),
				glm::vec4(0.0, 0.0, 1, 1)));

		}
	}
		vertexCount = vertexCount * vertexCount;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertexCount, &vertices[0], GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			sizeof(VertexFormat), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
			sizeof(VertexFormat),
			(void*)(offsetof(VertexFormat, VertexFormat::color)));
		glBindVertexArray(0);
		this->vao = vao;
		this->vbos.push_back(vbo);
		//this->vbos.push_back(ibo);
}

void Sphere::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix)
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glUniform3f(glGetUniformLocation(program, "position"),
		position.x,
		position.y,
		position.z);
	glUniform3f(glGetUniformLocation(program, "camera_position"),
		cameraPosition.x,
		cameraPosition.y,
		cameraPosition.z);
	glUniform3f(glGetUniformLocation(program, "camera_rotation"),
		cameraRotation.x,
		cameraRotation.y,
		cameraRotation.z);
	glUniform3f(glGetUniformLocation(program, "rotation"),
		0.0f,
		0.0f,
		0.0f);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1,
		false, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);
	glPointSize(3);
	glDrawArrays(GL_POINTS, 0, vertexCount);
}

// function for moving sphere in space
// define that the surface lay on the -3 level
void Sphere::update()
{
	if (surfaceTouch())
	{
		if (speed.y >= 0)
		{
			position += speed;
			speed.y -= GRAVITY;
		}
		else
		{
			position.y = -3 + radius;
			speed = glm::vec3(0, 0, 0);
		}

	}
	else
	{
		position += speed;
		speed.y -= GRAVITY;
	}
		
}

// checking if the sphere touch the surface
bool Engine::Rendering::Models::Sphere::surfaceTouch()
{
	if (position.y - radius <= -3) return true;
	return false;
}

void Engine::Rendering::Models::Sphere::push(glm::vec3 speed)
{
	this->speed = speed;
}








