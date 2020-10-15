#include "GameManager.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>

#include "TextureManager.h"
#include "Ball.h"
#include "Paddle.h"

GameManager* GameManager::s_instance = nullptr;

GameManager* GameManager::Get()
{
	return s_instance;
}

void GameManager::RegisterInstance(GameManager* _instance)
{
	assert(s_instance == nullptr);
	s_instance = _instance;
}

void GameManager::UnregisterInstance(GameManager* _instance)
{
	assert(s_instance == _instance);
	s_instance = nullptr;
}

SDL_Window* GameManager::GetWindow() const
{
	return m_window;
}

SDL_Renderer* GameManager::GetRenderer() const
{
	return m_renderer;
}

bool GameManager::Initialize()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	//Create window
	m_window = SDL_CreateWindow("Pong",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_windowWidth,
		m_windowHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (m_window == nullptr)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetWindowMinimumSize(m_window, 720, 480);

	//Create vsynced renderer for window
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(flags)))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

void GameManager::Destroy()
{
	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

const int GameManager::GetWindowWidth() const
{
	return m_windowWidth;
}

const int GameManager::GetWindowHeight() const
{
	return m_windowHeight;
}

void GameManager::PlayGame()
{
	bool quit = false;
	SDL_Event e;

	Ball ball = Ball(
		Position{ GameManager::Get()->GetWindowWidth() / 2.0f, GameManager::Get()->GetWindowHeight() / 2.0f },
		TextureManager::Get()->GetBallTexture());
	ball.UpdateVelocity(Direction::left);

	Paddle player = Paddle(
		Position{ GameManager::Get()->GetWindowWidth() - 30.0f,GameManager::Get()->GetWindowHeight() / 2.0f - TextureManager::Get()->GetPlayerPaddleTexture().GetHeight() / 2 },
		TextureManager::Get()->GetPlayerPaddleTexture());

	Paddle computer = Paddle(
		Position{ GameManager::Get()->GetWindowWidth() / 100.0f, GameManager::Get()->GetWindowHeight() / 2.0f - TextureManager::Get()->GetComputerPaddleTexture().GetHeight() / 2 },
		TextureManager::Get()->GetComputerPaddleTexture());

	Collider wallUp = Collider(ColliderBox{ 0, 0, (float)GameManager::Get()->GetWindowWidth(), 5 }, Type::staticCollider);
	Collider wallDown = Collider(ColliderBox{ 0, (float)GameManager::Get()->GetWindowHeight() - 10, (float)GameManager::Get()->GetWindowWidth(), 5 }, Type::staticCollider);

	m_colliderList.push_back(&wallUp);
	m_colliderList.push_back(&wallDown);
	m_colliderList.push_back(&player);
	m_colliderList.push_back(&computer);

	while (!quit)
	{
		//Input events
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.type == SDL_WINDOWEVENT)
			{
				int windowWidth;
				int windowHeight;
				SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

				player.ResetPosition(m_windowWidth - windowWidth, m_windowHeight - windowHeight);

				m_windowWidth = windowWidth;
				m_windowHeight = windowHeight;
			}

			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: player.UpdateVelocity(Direction::up); break;
				case SDLK_DOWN: player.UpdateVelocity(Direction::down); break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: player.UpdateVelocity(Direction::down); break;
				case SDLK_DOWN: player.UpdateVelocity(Direction::up); break;
				}
			}
		}

		//Game Logic

		ball.Update();
		player.Update();
		computer.Update();

		for (auto& collider : m_colliderList)
		{
			if (ball.Collide(*collider))
			{
				ball.SetVelocity(Position{ -ball.GetVelocity().x, -ball.GetVelocity().y });
			}
		}

		//Rendering
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderClear(m_renderer);

		SDL_SetRenderDrawColor(m_renderer, 70, 70, 70, 255);
		SDL_RenderDrawLine(m_renderer, m_windowWidth / 2, 0, m_windowWidth / 2, m_windowHeight);

		//TextureManager::Get()->RenderTextures(m_windowWidth, m_windowHeight);
		ball.Render();
		player.Render();
		computer.Render();

		SDL_RenderPresent(m_renderer);
	}
}
