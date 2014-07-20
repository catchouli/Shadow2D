#include "graphics/ShaderProgram.h"

#include <stdio.h>
#include <malloc.h>

namespace s2d
{
	ShaderProgram::ShaderProgram(const char* vs_filename, const char* fs_filename)
		: mShaderProg(0), mVertexShader(0), mFragmentShader(0)
	{
		size_t vs_len;
		size_t fs_len;

		char* vs_contents;
		char* fs_contents;

		// Read files
		bool vs_success = readFile(vs_filename, &vs_contents, &vs_len);
		bool fs_success = readFile(fs_filename, &fs_contents, &fs_len);

		// Return if file read failed
		if (!vs_success || !fs_success)
			return;

		// Compile shaders
		mVertexShader = compile(GL_VERTEX_SHADER, vs_filename, vs_contents);
		mFragmentShader = compile(GL_FRAGMENT_SHADER, fs_filename, fs_contents);

		// Return if compilation failed for either shader
		if (mVertexShader == 0 || mFragmentShader == 0)
		{
			// Delete created shaders
			if (mVertexShader != 0)
				glDeleteShader(mVertexShader);
			if (mFragmentShader != 0)
				glDeleteShader(mFragmentShader);

			mVertexShader = 0;
			mFragmentShader = 0;

			// Return
			return;
		}

		// Create shader program
		mShaderProg = glCreateProgram();
		glAttachShader(mShaderProg, mVertexShader);
		glAttachShader(mShaderProg, mFragmentShader);
		glLinkProgram(mShaderProg);
	}

	ShaderProgram::~ShaderProgram()
	{
		if (mShaderProg != 0)
			glDeleteProgram(mShaderProg);
		if (mVertexShader != 0)
			glDeleteShader(mVertexShader);
		if (mFragmentShader != 0)
			glDeleteShader(mFragmentShader);
	}

	void ShaderProgram::bind()
	{
		glUseProgram(mShaderProg);
	}

	ShaderProgram::operator GLuint()
	{
		return mShaderProg;
	}

	bool ShaderProgram::readFile(const char* filename, char** out_p, size_t* out_len)
	{
		FILE* fp;
		size_t len;
		char* buf;

		// Open file
		fp = fopen(filename, "rb");

		if (fp == NULL)
		{
			fprintf(stderr, "Failed to read file: %s\n", filename);
			return false;
		}

		// Get file length
		fseek(fp, 0, SEEK_END);
		len = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		// Allocate memory len + 1 for null terminator
		buf = (char*)malloc((len + 1) * sizeof(char));

		// Read full file
		fread(buf, 1, len, fp);

		// Write null terminator
		buf[len] = 0;

		// Output pointer and length
		*out_p = buf;
		*out_len = len;
	}

	GLuint ShaderProgram::compile(GLuint type, const char* filename, const char* source)
	{
		GLint compiled;
		GLuint shader;

		// Create shader
		shader = glCreateShader(type);

		// Set shader source
		glShaderSource(shader, 1, (const GLchar**)&source, NULL);

		// Compile shader
		glCompileShader(shader);

		// Get compile status
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			char* buf;
			GLint length;

			// Get error length
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			// Allocate memory
			buf = (char*)malloc(length);
			glGetShaderInfoLog(shader, length, &length, buf);

			fprintf(stderr, "Failed to compile shader %s: \n%s", filename, buf);

			// Cleanup
			free(buf);
			glDeleteShader(shader);

			return 0;
		}

		return shader;
	}
}