#include <iostream>    
#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GLFW/glfw3.h>    
#include "glm\glm.hpp"
#include <glm\gtc\matrix_transform.hpp>
#include "shader.hpp"
#include "controls.hpp"
#include <ctime>
#include <vector>
#include <cstdlib>
using namespace glm;
GLFWwindow* window;

#define N 500
void vertexSet(std::vector<glm::vec3> & g_vertex_buffer_data)
{
	glm::vec3 vertex;
	srand((unsigned)time(NULL));
	for (int i = 0; i < N; i++)
	{	
		vertex = glm::vec3(-1+(rand() % (100))*0.01, -1+(rand() % (100))*0.01,-1+(rand() % (100))*0.01);
		g_vertex_buffer_data.push_back(vertex);
		
	}
}

void vertexColor(std::vector<glm::vec3> & g_color_buffer_data)
{
	glm::vec3 color;
	srand((unsigned)time(NULL));
	for (int i = 0; i < N; i++)
	{
		color = glm::vec3((rand() % (100))*0.01, (rand() % (100))*0.01, (rand() % (100))*0.01);
		g_color_buffer_data.push_back(color);
	}
	
}

int main()
{

	if (!glfwInit())
	{
		fprintf(stderr, "GLFW failure");
		return -1;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//use Opengl 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	window = glfwCreateWindow(1024, 768, "Opengl", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "glfw failure,GPU wrong");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "glew failure");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glPointSize(10.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	std::vector<glm::vec3> g_vertex_buffer_data;
	vertexSet(g_vertex_buffer_data);
	std::vector<glm::vec3> g_color_buffer_data;
	vertexColor(g_color_buffer_data);
	

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(glm::vec3), &g_vertex_buffer_data[0], GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, g_color_buffer_data.size() * sizeof(glm::vec3), &g_color_buffer_data[0], GL_STATIC_DRAW);
	
	do
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_LINE_STRIP, 0, g_vertex_buffer_data.size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	glfwTerminate();
	return 0;

}



