#include <iostream>    
#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include "glm\glm.hpp"
#include <glm\gtc\matrix_transform.hpp>
#include "shader.hpp"
#include "controls.hpp"
#include <ctime>
#include <vector>
#include <cstdlib>
using namespace glm;
GLFWwindow* window;

#define N 100000
#define hilberN 6

/*
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
*/
void HilbertOne(std::vector<glm::vec3> & g_vertex_buffer_data)
{
	glm::vec3 vertex;
	//start 
	vertex = glm::vec3(0, 0, 0);
	g_vertex_buffer_data.push_back(vertex);
	//up
	vertex = glm::vec3(0, 1.0f, 0);
	g_vertex_buffer_data.push_back(vertex);
	//forward
	vertex = glm::vec3(0, 1.0f, -1.0f);
	g_vertex_buffer_data.push_back(vertex);
	//down
	vertex = glm::vec3(0, 0, -1.0f);
	g_vertex_buffer_data.push_back(vertex);
	//right
	vertex = glm::vec3(1.0f, 0, -1.0f);
	g_vertex_buffer_data.push_back(vertex);
	//up
	vertex = glm::vec3(1.0f, 1.0f, -1.0f);
	g_vertex_buffer_data.push_back(vertex);
	//foward
	vertex = glm::vec3(1.0f, 1.0f, 0);
	g_vertex_buffer_data.push_back(vertex);
	//down
	vertex = glm::vec3(1.0f, 0, 0);
	g_vertex_buffer_data.push_back(vertex);
}
void Hilbert(std::vector<glm::vec3> & g_vertex_buffer_data, int n)
{
	glm::vec3 vertex;
	//start
	HilbertOne(g_vertex_buffer_data);
	if (n != 1){
		float body_long = 1;
		for (int j = 2; j <= n; j++)
		{
			std::vector<glm::vec3> g_vertex_base = g_vertex_buffer_data;
			g_vertex_buffer_data.clear();
			float move = 0.5 / (pow(2, j-1) - 1);
			glm::vec3 d = glm::vec3(0.5f, 0.5f, 0.5f);
			//start
			for (int i = 0; i < g_vertex_base.size(); i++)
			{
				//z軸の回転
				glm::vec3 az = glm::vec3(0, 1, 0);
				glm::vec3 bz = glm::vec3(-1, 0, 0);
				glm::vec3 cz = glm::vec3(0, 0, 1);
				glm::mat3 matrix_z = glm::mat3(az,bz,cz);
				//y軸の回転
				glm::vec3 ay = glm::vec3(0, 0, 1);
				glm::vec3 by = glm::vec3(0, 1, 0);
				glm::vec3 cy = glm::vec3(-1, 0, 0);
				glm::mat3 matrix_y = glm::mat3(ay, by, cy);
				g_vertex_buffer_data.push_back(matrix_y*(matrix_z * g_vertex_base[i]) * d);
			}
		
			//up
			std::vector<glm::vec3> g_vertex_new;
			for (int i = 0; i < g_vertex_base.size(); i++)
			{
				//x軸の回転
				glm::vec3 ax = glm::vec3(1, 0, 0);
				glm::vec3 bx = glm::vec3(0, 0, 1);
				glm::vec3 cx = glm::vec3(0, -1, 0);
				glm::mat3 matrix_x = glm::mat3(ax, bx, cx);
				//z軸の回転
				glm::vec3 az = glm::vec3(0, -1, 0);
				glm::vec3 bz = glm::vec3(1, 0, 0);
				glm::vec3 cz = glm::vec3(0, 0, 1);
				glm::mat3 matrix_z = glm::mat3(az, bz, cz);
				glm::vec3 e = glm::vec3(0, 0.5 * body_long + move, 0);
				g_vertex_new.push_back(matrix_x * (matrix_z * g_vertex_base[i]) * d + e);
				g_vertex_buffer_data.push_back(g_vertex_new[i]);
			}

			//back
			for (int i = 0; i < g_vertex_base.size(); i++)
			{
				glm::vec3 e = glm::vec3(0, 0, -0.5 * body_long - move);
				g_vertex_buffer_data.push_back(g_vertex_new[i] + e);
			}
			
			//down
			g_vertex_new.clear();
			for (int i = 0; i < g_vertex_base.size(); i++)
			{
				//x軸の回転
				glm::vec3 ax = glm::vec3(1, 0, 0);
				glm::vec3 bx = glm::vec3(0,-1, 0);
				glm::vec3 cx = glm::vec3(0, 0, -1);
				glm::mat3 matrix_x = glm::mat3(ax, bx, cx);
				glm::vec3 e = glm::vec3(0, 0.5f * body_long,- body_long -move);
				g_vertex_new.push_back(matrix_x * g_vertex_base[i] * d + e);
				g_vertex_buffer_data.push_back(g_vertex_new[i]);
			}
			
			//right
			for (int i = 0; i < g_vertex_base.size(); i++)
			{
				glm::vec3 e = glm::vec3(0.5 * body_long + move, 0, 0);
				g_vertex_buffer_data.push_back(g_vertex_new[i] + e);
			}
	

			//up
			g_vertex_new.clear();
			for (int i = 0; i < g_vertex_base.size(); i++)
			{
				//y軸の回転
				glm::vec3 ay = glm::vec3(0, 0, 1);
				glm::vec3 by = glm::vec3(0, 1, 0);
				glm::vec3 cy = glm::vec3(-1, 0, 0);
				glm::mat3 matrix_y = glm::mat3(ay, by, cy);
				//z軸の回転
				glm::vec3 az = glm::vec3(0, 1, 0);
				glm::vec3 bz = glm::vec3(-1, 0, 0);
				glm::vec3 cz = glm::vec3(0, 0, 1);
				glm::mat3 matrix_z = glm::mat3(az, bz, cz);
				glm::vec3 e = glm::vec3(body_long + move, 0.5* body_long + move, -body_long - move);
				g_vertex_new.push_back(matrix_z * (matrix_y*g_vertex_base[i])*d+e);
				g_vertex_buffer_data.push_back(g_vertex_new[i]);
			}


			//back
			for (int i = 0; i < g_vertex_base.size(); i++)
			{
				glm::vec3 e = glm::vec3(0, 0, 0.5 * body_long +move);
				g_vertex_buffer_data.push_back(g_vertex_new[i] + e);
			}

			//down
			g_vertex_new.clear();
			for (int i = 0; i < g_vertex_base.size(); i++)
			{
				//y軸の回転
				glm::vec3 ay = glm::vec3(0, 0, -1);
				glm::vec3 by = glm::vec3(0, 1, 0);
				glm::vec3 cy = glm::vec3(1, 0, 0);
				glm::mat3 matrix_y = glm::mat3(ay, by, cy);
				//x軸の回転
				glm::vec3 ax = glm::vec3(1, 0, 0);
				glm::vec3 bx = glm::vec3(0, 0, -1);
				glm::vec3 cx = glm::vec3(0, 1, 0);
				glm::mat3 matrix_x = glm::mat3(ax, bx, cx);
				glm::vec3 e = glm::vec3(body_long+move, body_long/2, 0);
				g_vertex_buffer_data.push_back(matrix_x*(matrix_y * g_vertex_base[i]) * d + e );
			}

			body_long = body_long + move;
		}
	}	
}

void vertexSet(std::vector<glm::vec3> & g_vertex_buffer_data)
{
	Hilbert(g_vertex_buffer_data, hilberN);
}

void vertexColor(std::vector<glm::vec3> & g_color_buffer_data,int n)
{
	glm::vec3 color;
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++)
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
	vertexColor(g_color_buffer_data, g_vertex_buffer_data.size());
	

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



