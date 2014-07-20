#ifndef SHADOW2D_SHADERPROGRAM_H
#define SHADOW2D_SHADERPROGRAM_H

#include <gl/glew.h>

namespace s2d
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const char* vs_filename, const char* fs_filename);
		~ShaderProgram();

		void bind();

		operator GLuint();

	protected:
		bool readFile(const char* filename, char** out_p, size_t* out_len);
		GLuint compile(GLuint type, const char* filename, const char* source);

	private:
		GLuint mVertexShader;
		GLuint mFragmentShader;
		GLuint mShaderProg;
	};
}

#endif /* SHADOW2D_SHADERPROGRAM_H */
