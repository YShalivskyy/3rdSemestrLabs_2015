#include "ShaderManager.h" 


using namespace Engine::Managers;

std::map<std::string, GLuint> ShaderManager::programs;

ShaderManager::ShaderManager(void) {}

ShaderManager::~ShaderManager(void)
{
	for (auto iterator = programs.begin(); iterator != programs.end(); ++iterator)
	{
		GLuint value = iterator->second;
		glDeleteProgram(value);
	}
	programs.clear();
}

std::string ShaderManager::readShader(const std::string& filename)
{

	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file " << filename.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderManager::createShader(GLenum shaderType,
	const std::string& source,
	const std::string& shaderName)
{
	int compileResult = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	//check for errors
	if (compileResult == GL_FALSE)
	{

		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shaderLog[0] << std::endl;
		return 0;
	}
	return shader;
}

void ShaderManager::createProgram(const std::string& shaderName,
	const std::string& vertexShaderFilename,
	const std::string& fragmentShaderFilename)
{

	//read the shader files and save the code
	std::string vertexShaderCode = readShader(vertexShaderFilename);
	std::string fragmentShaderCode = readShader(fragmentShaderFilename);

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

	int linkResult = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	//check for link errors
	if (linkResult == GL_FALSE)
	{

		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &programLog[0] << std::endl;
	}
	programs[shaderName] = program;
}

const GLuint ShaderManager::getShader(const std::string& shaderName)
{
	return programs.at(shaderName);
}
