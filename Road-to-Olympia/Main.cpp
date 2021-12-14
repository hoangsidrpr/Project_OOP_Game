#include "Game.h"

int main()
{
	Game G(2000,2000, L"Crossing Game",false);
	srand(time(NULL));

	G.Processing();
	system("pause >nul");
}