#include "GameManager.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>

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
	m_window = SDL_CreateWindow("Tic Tac Toe",
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

	if (IMG_Init(IMG_INIT_JPG) < 0)
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

	//Event handler
	SDL_Event e;

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
				SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
			}
		}

		//Game Logic

		//Rendering
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderClear(m_renderer);


		SDL_RenderPresent(m_renderer);
	}
}
