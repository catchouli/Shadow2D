#include "app/Shadow2D.h"

#include "graphics/ShaderProgram.h"
#include "graphics/ShadingAttributes.h"

namespace s2d
{
	void Shadow2D::render()
	{
		static ShaderProgram fp("first_pass.vs.glsl", "first_pass.fs.glsl");
		static ShaderProgram sp("second_pass.vs.glsl", "second_pass.fs.glsl");

		static bool init = false;
		static GLuint fbo;
		static GLuint colour_tex;
		static GLuint depth_tex;

		static GLuint colour_texture_loc;
		static GLuint depth_texture_loc;

		static GLuint light_pos_loc = glGetUniformLocation(sp, "light_pos");
		static GLuint screen_dim_loc = glGetUniformLocation(sp, "screen_dimensions");

		glProgramUniform2f(sp, screen_dim_loc, (float)getWidth(), (float)getHeight());

		if (glfwGetMouseButton(_window, 0))
		{
			double x, y;

			glfwGetCursorPos(_window, &x, &y);

			x /= (double)getWidth();
			y /= (double)getHeight();

			x *= 2.0f;
			y *= 2.0f;

			x = 1.0f - x;
			y -= 1.0f;

			glProgramUniform2f(sp, light_pos_loc, x, y);
		}
		
		if (!init)
		{
			init = true;

			int width, height;
			glfwGetWindowSize(_window, &width, &height);

			colour_texture_loc = glGetUniformLocation(sp, "colour");
			depth_texture_loc = glGetUniformLocation(sp, "depth");

			glGenTextures(1, &colour_tex);
			glBindTexture(GL_TEXTURE_2D, colour_tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, 0);

			glGenTextures(1, &depth_tex);
			glBindTexture(GL_TEXTURE_2D, depth_tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colour_tex, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_tex, 0);

			checkGlError();
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_ONE, GL_ONE);

		glEnable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		fp.bind();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		//glRotatef(glfwGetTime() * 15.0f, 0, 0, 1.0f);

		//glBegin(GL_TRIANGLES);
		//glVertex2f(-1.0f, -1.0f);
		//glVertex2f(0.0f, -1.0f);
		//glVertex2f(0.0f, 0.0f);
		//glEnd();

		for (int i = 0; i < CIRCLE_COUNT; ++i)
		{
			glPushMatrix();
			glLoadIdentity();

			glTranslatef(circle_positions[i].x, circle_positions[i].y, 0.0f);

			glScalef(circle_sizes[i], circle_sizes[i], 1.0f);

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, 0, _circleVertexArray);
			glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_DIVISIONS);
			glDisableClientState(GL_VERTEX_ARRAY);

			glPopMatrix();
		}

		glPopMatrix();

		glDisable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glBlitFramebuffer(0, 0, getWidth(), getHeight(), 0, 0, getWidth(), getHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR);

		sp.bind();

		glEnable(GL_TEXTURE_2D);

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, colour_tex);
		//glProgramUniform1i(sp, colour_texture_loc, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depth_tex);
		glProgramUniform1i(sp, depth_texture_loc, 1);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(1.0f, -1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
		glEnd();
	}
}
