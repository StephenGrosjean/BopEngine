#ifndef Game_h
#define Game_h
#include "SDL.h"
#include <iostream>
#include <vector>
#include "Vector2D.h"
#include "SDL_image.h"
#include "AssetManager.h"
#include "InputManager.h"

class ColliderComponent;

class Game {

public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	
	void SetRunning(bool value);
	bool GetRunning();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static AssetManager* assetManager;
	static InputManager* inputManager;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles,
		groupValidTiles
	};


private:
	bool isRunning = false;
	int counter = 0;
	SDL_Window* window;
	bool isPlayer1Valid;
	bool isPlayer2Valid;
};



#endif /* Game_h */
