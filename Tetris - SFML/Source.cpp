#include "GameEngine.h"

int main() {
    //Init Game engine
    GameEngine game;

    while (game.running())
    {
        //Update
        game.update();

        //Render
        game.render();
    }
	return 0;
}