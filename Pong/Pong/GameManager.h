#pragma once

#include <SDL.h>

#include <assert.h> 
#include "Texture.h"

struct Position
{
	float x;
	float y;
};

enum class Direction
{
	up,
	down
};

class GameManager
{
public:
	static GameManager* Get();

	static void RegisterInstance(GameManager* _instance);
	static void UnregisterInstance(GameManager* _instance);

	SDL_Window* GetWindow() const;
	SDL_Renderer* GetRenderer() const;

	bool Initialize();
	void Destroy();

	const int GetWindowWidth() const;
	const int GetWindowHeight() const;

	void PlayGame();

private:
	static GameManager* s_instance;

	int m_windowWidth = 720;
	int m_windowHeight = 480;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};

