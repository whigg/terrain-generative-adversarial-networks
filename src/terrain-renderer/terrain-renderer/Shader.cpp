#include "stdafx.h"
#include "Shader.h"
#include <GLFX/glfx.h>
#include "Logger.h"

Shader::Shader()
{
	effect = glfxGenEffect();
}

Shader::~Shader()
{
	glfxDeleteEffect(effect);
}

int Shader::compileProgram(const char * effectFilePath, const char * programName) const
{
	bool bParsingSuccess = glfxParseEffectFromFile(effect, effectFilePath);
	if (!bParsingSuccess)
	{
		handleGLFXError();
		return -1;
	}

	int program = glfxCompileProgram(effect, programName);
	if (program == -1)
	{
		handleGLFXError();
		return -1;
	}
	
	return program;
}

const char* Shader::getProgramName(int programIndex) const
{
	return glfxGetProgramName(effect, programIndex);
}

void Shader::handleGLFXError(void) const
{
	std::string errorLog = glfxGetEffectLog(effect);
	INFO_LOG("GLFX error log : {}", errorLog);
}