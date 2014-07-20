#include "app/Shadow2D.h"

const int INITIAL_WIDTH = 800;
const int INITIAL_HEIGHT = 600;

using namespace s2d;

int main(int argc, char** argv)
{
	Shadow2D shadow2d(INITIAL_WIDTH, INITIAL_HEIGHT);

	// Run until exit
	while (shadow2d.run());

	return 0;
}
