#include "GameManager.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <math.h>
#include <string>

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
	m_ball = nullptr;
	m_player = nullptr;
	m_computer = nullptr;
	m_wallUp = nullptr;
	m_wallDown = nullptr;

	delete m_ball;
	delete m_player;
	delete m_computer;
	delete m_wallUp;
	delete m_wallDown;

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

	m_ball = &Ball(
		Position{ GameManager::Get()->GetWindowWidth() / 2.0f, GameManager::Get()->GetWindowHeight() / 2.0f },
		TextureManager::Get()->GetBall());

	m_player = &Paddle(
		Position{ GameManager::Get()->GetWindowWidth() - 30.0f,GameManager::Get()->GetWindowHeight() / 2.0f - TextureManager::Get()->GetPlayerPaddle().GetHeight() / 2 },
		TextureManager::Get()->GetPlayerPaddle());

	m_computer = &Paddle(
		Position{ GameManager::Get()->GetWindowWidth() / 100.0f, GameManager::Get()->GetWindowHeight() / 2.0f - TextureManager::Get()->GetComputerPaddle().GetHeight() / 2 },
		TextureManager::Get()->GetComputerPaddle());

	m_wallUp = &Collider(ColliderBox{ 0, 0, (float)GameManager::Get()->GetWindowWidth(), 5 }, Type::staticCollider);
	m_wallDown = &Collider(ColliderBox{ 0, (float)GameManager::Get()->GetWindowHeight() - 10, (float)GameManager::Get()->GetWindowWidth(), 5 }, Type::staticCollider);

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

				m_player->UpdateToWindow(m_windowWidth - windowWidth, m_windowHeight - windowHeight);

				m_windowWidth = windowWidth;
				m_windowHeight = windowHeight;
			}

			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: m_player->UpdateVelocity(Direction::up); break;
				case SDLK_DOWN: m_player->UpdateVelocity(Direction::down); break;

				case SDLK_w: m_computer->UpdateVelocity(Direction::up); break;
				case SDLK_s: m_computer->UpdateVelocity(Direction::down); break;
				}
			}
			else if (e.type == SDL_KEYUP && e.key.repeat == 0)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: m_player->UpdateVelocity(Direction::down); break;
				case SDLK_DOWN: m_player->UpdateVelocity(Direction::up); break;

				case SDLK_w: m_computer->UpdateVelocity(Direction::down); break;
				case SDLK_s: m_computer->UpdateVelocity(Direction::up); break;
				}
			}
		}

		//Game Logic

		m_ball->Update();
		m_player->Update();
		m_computer->Update();

		CheckCollisions();

		//Rendering
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderClear(m_renderer);

		SDL_SetRenderDrawColor(m_renderer, 70, 70, 70, 255);
		SDL_RenderDrawLine(m_renderer, m_windowWidth / 2, 0, m_windowWidth / 2, m_windowHeight);

		//TextureManager::Get()->RenderTextures(m_windowWidth, m_windowHeight);
		m_ball->Render();
		m_player->Render();
		m_computer->Render();

		TextureManager::Get()->GetComputerScore().Render(m_windowWidth / 4, 10);
		TextureManager::Get()->GetPlayerScore().Render(m_windowWidth - m_windowWidth / 4, 10);

		SDL_RenderPresent(m_renderer);
	}
}

void GameManager::RestartLevel()
{
	m_ball->ResetPosition();
	m_player->ResetPosition();
	m_computer->ResetPosition();
}

void GameManager::RestartGame()
{
	RestartLevel();
	m_computerScore = 0;
	m_playerScore = 0;
}

void GameManager::CheckCollisions()
{
	if (m_ball->Collide(*m_player))
	{
		float y = m_ball->GetSpeed();
		float t = ((m_ball->GetPosition().y - m_player->GetPosition().y) / TextureManager::Get()->GetPlayerPaddle().GetHeight()) + 0.5f;
		if (t > 0 && t < 1)
		{
			y = -std::abs(m_ball->GetVelocity().y) - y/2;
		}

		m_ball->SetVelocity(Position{ -std::abs(m_ball->GetVelocity().x), y });
	}

	if (m_ball->Collide(*m_computer))
	{
		float y = m_ball->GetSpeed();
		float t = ((m_ball->GetPosition().y - m_computer->GetPosition().y) / TextureManager::Get()->GetComputerPaddle().GetHeight()) + 0.5f;
		if (t > 0 && t < 1)
		{
			y = std::abs(m_ball->GetVelocity().y) - y/2;
		}
		m_ball->SetVelocity(Position{ std::abs(m_ball->GetVelocity().x), y });
	}

	if (m_ball->Collide(*m_wallUp))
	{
		m_ball->SetVelocity(Position{ m_ball->GetVelocity().x, -m_ball->GetVelocity().y });
	}

	if (m_ball->Collide(*m_wallDown))
	{
		m_ball->SetVelocity(Position{ m_ball->GetVelocity().x, -m_ball->GetVelocity().y });
	}

	if (m_ball->GetPosition().x < 0)
	{
		//score for the player
		m_playerScore++;
		if (CheckEndGame())
		{
			RestartGame();
		}
		else 
		{
			RestartLevel();
		}

		TextureManager::Get()->GetPlayerScore().LoadFromRenderedText(std::to_string(m_playerScore));

	}

	if (m_ball->GetPosition().x > GameManager::Get()->GetWindowWidth() - TextureManager::Get()->GetPlayerPaddle().GetWidth())
	{
		//score for the computer
		m_computerScore++;
		if (CheckEndGame())
		{
			RestartGame();
		}
		else
		{
			RestartLevel();
		}

		TextureManager::Get()->GetComputerScore().LoadFromRenderedText(std::to_string(m_computerScore));
	}
}

bool GameManager::CheckEndGame()
{
	return (m_computerScore > 11) || (m_playerScore > 11);
}
