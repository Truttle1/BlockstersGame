#include "../libraries/raylib.h"
#include "Blocksters0.h"

#include "../GameWindow.h"
GameWindow * game = new GameWindow();
Camera2D* camera = new Camera2D();

int main()
{
	InitAudioDevice();
	game->init(camera);
	while(!WindowShouldClose())
	{
		game->tick();
		BeginDrawing();
		BeginMode2D(*camera);
		{
			game->render();
			EndMode2D();
			game->drawGUI();
		}
		EndDrawing();
	}

	return 0;
}


