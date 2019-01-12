#ifndef SHADER_H
#define SHADER_H

class Shader
{
private:
	int effect;
public:
	Shader();
	~Shader();

	int 		compileProgram(const char *effectFilePath, const char *programName) const;
	const char* getProgramName(int programIndex) const;
private:
	void		handleGLFXError(void) const;
};

#endif