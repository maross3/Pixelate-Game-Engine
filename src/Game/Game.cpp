#include "Game.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include "../ECS/ECS.h"

Game::Game()
{
	_isRunning = false;
	spdlog::info("Constructor Called");
}

Game::~Game()
{
	spdlog::info("Destructor Called");
}

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		spdlog::critical("Failed to initialize SDL");

	SDL_DisplayMode displayMode{};
	SDL_GetCurrentDisplayMode(0, &displayMode);

	windowWidth = displayMode.w;
	windowHeight = displayMode.h;
	
	_window = SDL_CreateWindow(
		"Pixelate V 0.1.0",
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		windowWidth, windowHeight, 
		SDL_WINDOW_BORDERLESS);

	if (!_window)
		spdlog::critical("Error Constructing window.");

	_renderer = SDL_CreateRenderer(_window, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!_renderer)
		spdlog::critical("Error Constructing renderer.");

	SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
	_isRunning = true;
}


void Game::Setup()
{
	// TODO
	// Entity tank = _registry.CreateEntity();
	// tank.AddComponent<TransformComponent>();
	// tank.AddComponent<BoxColliderComponent>();
	// tank.AddComponent<SpriteComponent>("./assets/images/tank-tiger-right.png");
}

void Game::Run()
{
	Setup();
	while (_isRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Destroy() const
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;

	// pass by ref, not passing entire struct, just memory address

	while (SDL_PollEvent(&sdlEvent))
	{
		switch(sdlEvent.type)
		{
		case SDL_QUIT:
			_isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				_isRunning = false;
			break;
		default: break;
		}
	}

}

void Game::Render() const
{
	SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 255);
	SDL_RenderClear(_renderer);

	// TODO: Render the game objects


	SDL_RenderPresent(_renderer);
}

void Game::Update()
{
	const int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - _msPrevFrame);

	if(timeToWait > 0 && timeToWait <= MS_PER_FRAME)
		SDL_Delay(timeToWait);

	deltaTime = (SDL_GetTicks() - _msPrevFrame) / 1000.0;
	_msPrevFrame = SDL_GetTicks();

	// TODO:
	// MovementSystem.Update();
	// CollisionSystem.Update();
	// DamageSystem.Update();
}

