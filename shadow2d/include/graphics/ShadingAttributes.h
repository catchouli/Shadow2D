#ifndef SHADOW2D_SHADINGATTRIBUTES_H
#define SHADOW2D_SHADINGATTRIBUTES_H

#include <stdio.h>
#include <glm/glm.hpp>

namespace s2d
{
	struct light_t
	{
		bool enabled;
		glm::vec3 light_pos;
		glm::vec3 light_col;
	};

	struct shading_attributes_t
	{
		int light_count;
		light_t lights[10];
	};

	GLint getLocation(GLuint program, const char* name)
	{
		GLint loc = glGetUniformLocation(program, "shading_attributes.col");

		if (loc < 0)
		{
			fprintf(stderr, "Failed to get loctaion for uniform %s\n", name);
			fprintf(stderr, "Press return to continue\n", name);
			getchar();
			exit(1);
		}
	}

	inline void update_shading_attributes(GLuint program, const shading_attributes_t& shading_attributes)
	{
		GLint loc;

		//loc = getLocation(program, "shading_attributes.col");
		//glProgramUniform3f(program, loc, shading_attributes.col.r, shading_attributes.col.g, shading_attributes.col.b);
	}
}

#endif /* SHADOW2D_SHADINGATTRIBUTES_H */
