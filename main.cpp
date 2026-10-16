#include <Engine.h>

using friday::Engine;

int main() {
	Engine e("Game", 800, 600);
	if (e.Init()) {
		e.Run();
	}

	return 0;
}