#include "Application2D.h"

int main() {
	
	auto app = new Application2D();
	app->run("Tic Tac Toe", 460, 460, false);
	delete app;

	return 0;
}


//Modified application cpp in bootstrap to stop resizable windows
//Modified Application2d in now TICTACTOE solution to run tictactoe game