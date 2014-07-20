#include "app/Shadow2D.h"

namespace s2d
{
	void Shadow2D::resize_callback(GLFWwindow* window,
		int32_t width, int32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Shadow2D::mouse_move_callback(GLFWwindow* window,
		double x, double y)
	{

	}

	void Shadow2D::mouse_callback(GLFWwindow* window, int32_t button,
		int32_t action, int32_t mods)
	{

	}

	void Shadow2D::key_callback(GLFWwindow* window, int32_t key,
		int32_t scancode, int32_t action, int32_t mods)
	{
		Application::_default_key_callback(window, key, scancode, action, mods);
	}
}