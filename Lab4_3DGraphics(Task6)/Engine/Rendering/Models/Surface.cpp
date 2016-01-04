#include "Surface.h"

using namespace Engine::Rendering::Models;
using namespace Engine::Rendering;


Engine::Rendering::Models::Surface::Surface() :
	Surface(0)
{
}

Engine::Rendering::Models::Surface::Surface(float a) :
	surfaceLevel(a)
{
}

Engine::Rendering::Models::Surface::~Surface()
{
}

void Surface::create()
{
	GLuint vao;
	GLuint vbo;
	//GLuint ibo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(
		glm::vec3(-1000,
			surfaceLevel,
			-1000),
		glm::vec4(1.0, 1.0, 1.0, 1)));
	vertices.push_back(VertexFormat(
		glm::vec3(1000,
			surfaceLevel,
			-1000),
		glm::vec4(1.0, 1.0, 1.0, 1)));
	vertices.push_back(VertexFormat(
		glm::vec3(1000,
			surfaceLevel,
			1000),
		glm::vec4(1.0, 1.0, 1.0, 1)));
	vertices.push_back(VertexFormat(
		glm::vec3(-1000,
			surfaceLevel,
			1000),
		glm::vec4(1.0, 1.0, 1.0, 1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);


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

void Surface::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix)
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

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Surface::update()
{

}

