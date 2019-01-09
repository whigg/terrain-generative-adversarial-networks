#include "stdafx.h"
#include "sa-shader.h"
#include <GLFX/glfx.h>
#include <stdio.h>

SaShader::SaShader()
{
	effect = glfxGenEffect();
}

SaShader::~SaShader()
{
	glfxDeleteEffect(effect);
}

int SaShader::compileProgram(const char * effectFilePath, const char * programName) const
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

const char * SaShader::getProgramName(int programIndex) const
{
	return glfxGetProgramName(effect, programIndex);
}

void SaShader::handleGLFXError(void) const
{
	const char* errorLog = glfxGetEffectLog(effect);
	fprintf( stderr, "GLFX : %s\n", errorLog );
}
