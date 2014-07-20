#include "app/Shadow2D.h"

#include <math.h>
#include <time.h>

namespace s2d
{
	Shadow2D::Shadow2D(int32_t width, int32_t height,
		const char* title, bool hidden)
		: Application(width, height, title, hidden)
	{
		// Register callbacks
		glfwSetWindowSizeCallback(_window, resize_callback);
		glfwSetCursorPosCallback(_window, mouse_move_callback);
		glfwSetMouseButtonCallback(_window, mouse_callback);
		glfwSetKeyCallback(_window, key_callback);

		// Calculate step
		float step = (float)((2 * 3.1415926535897) / (double)CIRCLE_DIVISIONS);

		// Build vertex array
		for (int i = 0; i < CIRCLE_DIVISIONS; ++i)
		{
			_circleVertexArray[2 * i + 0] = 0.5f * cos(step * i);
			_circleVertexArray[2 * i + 1] = 0.5f * sin(step * i);
		}

		// Generate circles
		srand(time(0));
		for (int i = 0; i < CIRCLE_COUNT; ++i)
		{
			circle_sizes[i] = 0.5f * (rand() / (float)RAND_MAX);
			circle_positions[i] = glm::vec2(2.0f * (rand() / (float)RAND_MAX) - 1.0f, 2.0f * (rand() / (float)RAND_MAX) - 1.0f);
		}
	}
}
