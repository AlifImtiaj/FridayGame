#include <Engine.h>

using Friday::Engine;

int main() {
	Engine e("Game", 1280, 720);
	if (e.Init()) {
		e.Run();
	}

	return 0;
}