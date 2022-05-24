#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib") 

#include <iostream>
#include "Shader.h"

void renderScene();
void keyInput(unsigned char key, int x, int y);
void resize(int w, int h);
void setup();

Shader shader;
const char* vertexPath = "vertexShader.glsl";
const char* fragmentPath = "fragmentShader.glsl";

float square[] = {
	//x      y      z		 r	   g     b
	20.0f, 20.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	80.0f, 20.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	20.0f, 80.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	80.0f, 80.0f, 0.0f,		0.0f, 1.0f, 0.0f
};
float triangle[] = {
	30.0f, 30.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	70.0f, 30.0f, 1.0f,		1.0f, 0.0f, 0.0f,
	30.0f, 70.0f, 1.0f,		1.0f, 0.0f, 0.0f
};

glm::mat4 modelViewMat(1.0f);
glm::mat4 projMat(1.0f);

GLuint uniformModelViewMat, uniformProjMat;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("im doing my best");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glewExperimental = true;
	glewInit();
	
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyInput);
	//glutReshapeFunc(resize);

	setup();

	glutMainLoop();
	return 0;
}

GLuint VBO[2];
GLuint VAO[2];

void setup()
{
	shader.CompileEverythingFromFiles(vertexPath, fragmentPath);
	shader.UseShader();

	
	glGenBuffers(2, VBO);
	glGenVertexArrays(2, VAO);

	

	//std::cout << glGetError() << std::endl;

	uniformModelViewMat = shader.GetModelViewMatLoc();
	uniformProjMat = shader.GetProjMatLoc();

	glm::mat4 projMat = glm::ortho(0.0f, 100.0f, 0.0f, 100.0f, -1.0f, 1.0f);
	glm::mat4 modelViewMat(1.0f);
	

	glUniformMatrix4fv(uniformProjMat, 1, GL_TRUE, glm::value_ptr(projMat));
	glUniformMatrix4fv(uniformModelViewMat, 1, GL_TRUE, glm::value_ptr(modelViewMat)); //camera xyz rotation upVector

	//std::cout << glGetError() << std::endl;

	//
	//glBindVertexArray(VAO[1]);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(triangle[0]) * 18, NULL, GL_STATIC_DRAW);
	//
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangle[0]) * 9, triangle);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangle[0]) * 9, sizeof(triangle[0]) * 9, &triangle[9]);
	//
	//glVertexPointer(3, GL_FLOAT, 0, nullptr);
	//glColorPointer(3, GL_FLOAT, 0, (GLvoid*)(sizeof(triangle[0]) * 9));

	
	
	std::cout << glGetError() << std::endl;
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	//
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	//glBindVertexArray(VAO[1]);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	

	glutSwapBuffers();
};

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -1.0f, 1.0f);
	//gluPerspective(40, 1, 4, 20);
	//glFrustum(-10, -10, 10, 10, 4, 20);

	//std::cout << glGetError() << std::endl;
	
	//glMatrixMode(GL_MODELVIEW);
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	}
}