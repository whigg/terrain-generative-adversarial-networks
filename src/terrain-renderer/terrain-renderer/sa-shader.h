#pragma once

class SaShader
{
private:
	int effect;
public:
	SaShader();
	~SaShader();

	int 		compileProgram(const char *effectFilePath, const char *programName) const;
	const char* getProgramName(int programIndex)									const;
private:
	void		handleGLFXError(void) const;
};