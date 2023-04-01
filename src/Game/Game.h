#pragma once
#include <SDL.h>

constexpr int FPS = 60;
constexpr int MS_PER_FRAME = 1000 / FPS;

class Game
{
private:
	int _msPrevFrame = 0;
	bool _isRunning;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

public:
	Game();
	~Game();

	void Initialize();
	void Run();
	void Destroy() const;

	static void Setup();
	void ProcessInput();
	void Update();
	void Render() const;

	double deltaTime = 0;
	int windowWidth;
	int windowHeight;
};

