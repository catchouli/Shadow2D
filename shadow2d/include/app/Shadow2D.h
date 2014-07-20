#ifndef SHADOW2D_SHADOW2D_H
#define SHADOW2D_SHADOW2D_H

#include "Application.h"

#include <glm/glm.hpp>

namespace s2d
{
	const int CIRCLE_DIVISIONS = 64;

	const int CIRCLE_COUNT = 10;

	class Shadow2D
		: public Application
	{
	public:
		Shadow2D(int32_t width, int32_t height,
			const char* title = "", bool hidden = false);

		// Callbacks
		static void resize_callback(GLFWwindow* window,
			int32_t width, int32_t height);
		static void mouse_move_callback(GLFWwindow* window,
			double x, double y);
		static void mouse_callback(GLFWwindow* window, int32_t button,
			int32_t action, int32_t mods);
		static void key_callback(GLFWwindow* window, int32_t key,
			int32_t scancode, int32_t action, int32_t mods);

	protected:
		void update(double dt) override;

		void render() override;

	private:
		float _circleVertexArray[CIRCLE_DIVISIONS * 2];

		float circle_sizes[CIRCLE_COUNT];
		glm::vec2 circle_positions[CIRCLE_COUNT];
	};
}

#endif /* SHADOW2D_SHADOW2D_H */
