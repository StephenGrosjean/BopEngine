#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

TileMap* map;
Manager manager;
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

Game::Game(){}
Game::~Game(){}

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) 
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{		
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
		}
		isRunning = true;
	}

	map = new TileMap();

	player.AddComponent<TransformComponent>(2);
	player.AddComponent<KeyboardController>();
	player.AddComponent<SpriteComponent>("Assets/player.png");
	player.AddComponent<ColliderComponent>();

	wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.AddComponent<SpriteComponent>("Assets/dirt.png");
	wall.AddComponent<ColliderComponent>("wall");
}

void Game::HandleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::Update()
{
	manager.Refresh();
	manager.Update();

	if (Collision::AABB(player.GetComponent<ColliderComponent>().collider,
		wall.GetComponent<ColliderComponent>().collider))
	{
		std::cout << "Collision" << std::endl;
	}
}

void Game::Render() 
{
	SDL_RenderClear(renderer);

	map->Draw();
	manager.Draw();
	SDL_RenderPresent(renderer);
}

void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}