#pragma once

#include <fstream>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();

	void CompileEverythingFromFiles(const char* vShader, const char* fShader);
	void UseShader();
	
	GLuint GetProjMatLoc();
	GLuint GetModelViewMatLoc();

	~Shader();

private:
	std::string ReadFromFile(const char* fileLocation);
	void ShaderCheckUp(GLenum shaderType);
	void DestroyShader();

	GLuint shaderID, vertexShader, fragmentShader;
	GLuint projMatLoc, modelViewMatLoc;
};

