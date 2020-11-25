#include "TextureManager.h"

#include <assert.h> 

#include "Texture.h"

TextureManager* TextureManager::s_instance = nullptr;

TextureManager* TextureManager::Get()
{
	return s_instance;
}
void TextureManager::RegisterInstance(TextureManager* _instance)
{
	assert(s_instance == nullptr);
	s_instance = _instance;
}

void TextureManager::UnregisterInstance(TextureManager* _instance)
{
	assert(s_instance == _instance);
	s_instance = nullptr;
}

void TextureManager::Initialize(SDL_Renderer* _renderer)
{
	m_ball = new Texture(_renderer);
	m_computerPaddle = new Texture(_renderer);
	m_playerPaddle = new Texture(_renderer);
	m_computerScore = new Texture(_renderer);
	m_playerScore = new Texture(_renderer);
	m_singleplayerMode = new Texture(_renderer);
	m_multiplayerMode = new Texture(_renderer);
}

void TextureManager::Destroy()
{
	delete m_ball;
	delete m_computerPaddle;
	delete m_playerPaddle;
	delete m_computerScore;
	delete m_playerScore;
	delete m_singleplayerMode;
	delete m_multiplayerMode;
}

void TextureManager::LoadTextures()
{
	m_ball->LoadFromFile("Textures/Ball.png");
	m_computerPaddle->LoadFromFile("Textures/Player1.png");
	m_playerPaddle->LoadFromFile("Textures/Player2.png");

	m_computerScore->SetFont(TTF_OpenFont("Textures/lovtony.ttf", 64));
	m_computerScore->LoadFromRenderedText("0");
	m_playerScore->SetFont(TTF_OpenFont("Textures/lovtony.ttf", 64));
	m_playerScore->LoadFromRenderedText("0");

	m_singleplayerMode->LoadFromFile("Textures/singleplayer.png");
	m_multiplayerMode->LoadFromFile("Textures/multiplayer.png");
}

Texture& TextureManager::GetBall() const
{
	return *m_ball;
}

Texture& TextureManager::GetPlayerPaddle() const
{
	return *m_playerPaddle;
}

Texture& TextureManager::GetComputerPaddle() const
{
	return *m_computerPaddle;
}

Texture& TextureManager::GetComputerScore() const
{
	return *m_computerScore;
}

Texture& TextureManager::GetPlayerScore() const
{
	return *m_playerScore;
}

Texture& TextureManager::GetSingleplayerMode() const
{
	return *m_singleplayerMode;
}

Texture& TextureManager::GetMultiplayerMode() const
{
	return *m_multiplayerMode;
}
