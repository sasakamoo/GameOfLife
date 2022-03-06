#include "App.h"

void App::start() {
	if (demo.Construct(640, 480, 1, 1))
		demo.Start();
}