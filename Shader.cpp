#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	vertexShader = 0;
	fragmentShader = 0;

	projMatLoc = 0;
	modelViewMatLoc = 0;
}

void Shader::CompileEverythingFromFiles(const char* vShader, const char* fShader)
{
	//ReadFromFile(vShader);
	std::string vs = ReadFromFile(vShader);
	std::string fs = ReadFromFile(fShader);
	const char* vert = vs.c_str();
	const char* frag = fs.c_str();

	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vert, nullptr);
	glCompileShader(vertexShader);
	ShaderCheckUp(GL_VERTEX_SHADER);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &frag, nullptr);
	glCompileShader(fragmentShader);
	ShaderCheckUp(GL_FRAGMENT_SHADER);

	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Error creating shader program\n");
	}

	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	GLint result = GL_FALSE;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		GLchar log[1024] = { 0 };
		glGetProgramInfoLog(shaderID, sizeof(log), NULL, log);
		printf("Error linking program: %s\n", log);
	}

	projMatLoc = glGetUniformLocation(shaderID, "projectionMatrix");
	modelViewMatLoc = glGetUniformLocation(shaderID, "modelViewMatrix");
}


std::string Shader::ReadFromFile(const char* fileLocation)
{
	std::string line;
	std::string content = { '\n' };
	std::ifstream file(fileLocation, std::ios::in);

	if (!file.is_open())
	{
		printf("The file couldn't be opened from %s\n", fileLocation);
	}
	else
	{
		while (std::getline(file, line))
		{
			content.append(line + '\n');
		}
		file.close();
	}
	//std::cout << content << std::endl;
	return content;
}

void Shader::ShaderCheckUp(GLenum shaderType)
{
	GLint result = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		GLchar log[1024] = { 0 };
		glGetShaderInfoLog(vertexShader, sizeof(log), NULL, log);
		printf("Error compiling %d shader: %s\n", shaderType, log);
	}
}


void Shader::UseShader()
{
	glUseProgram(shaderID);
}

GLuint Shader::GetProjMatLoc()
{
	return projMatLoc;
}
GLuint Shader::GetModelViewMatLoc()
{
	return modelViewMatLoc;
}

void Shader::DestroyShader()
{
	if (shaderID)
	{
		glDeleteProgram(shaderID);
	}
	shaderID = 0;
	vertexShader = 0;
	fragmentShader = 0;
}
Shader::~Shader()
{
	DestroyShader();
}

