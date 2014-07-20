#ifdef _WIN32

#include <stdlib.h>

struct HINSTANCE__;
typedef HINSTANCE__* HINSTANCE;

int main(int argc, char** argv);

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow)
{
	return main(__argc, __argv);
}

#endif