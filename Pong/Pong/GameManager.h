#pragma once

#include <SDL.h>

#include <assert.h> 

#include "Texture.h"

class Ball;
class Paddle;
class Collider;

struct Position
{
	float x;
	float y;
};

enum class Direction
{
	up,
	down,
	left,
	right
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
	void RestartGame();

private:
	void CheckCollisions();

private:
	static GameManager* s_instance;

	int m_windowWidth = 720;
	int m_windowHeight = 480;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	Ball* m_ball = nullptr;
	Paddle* m_player = nullptr;
	Paddle* m_computer = nullptr;

	Collider* m_wallUp = nullptr;
	Collider* m_wallDown = nullptr;

	int m_playerScore = 0;
	int m_computerScore = 0;
};

