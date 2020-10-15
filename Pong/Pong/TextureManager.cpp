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

void TextureManager::Initialize()
{
	m_ball = new Texture();
	m_computerPaddle = new Texture();
	m_playerPaddle = new Texture();
	m_computerScore = new Texture();
	m_playerScore = new Texture();

}

void TextureManager::Destroy()
{
	delete m_ball;
	delete m_computerPaddle;
	delete m_playerPaddle;
	delete m_computerScore;
	delete m_playerScore;
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
}

void TextureManager::RenderTextures(int _windowWidth, int _windowHeight)
{
	//m_ball->Render(_windowWidth / 2, _windowHeight / 2);
	m_computerPaddle->Render(_windowWidth / 100, _windowHeight / 2 - m_computerPaddle->GetHeight() / 2);
	//m_player2Paddle->Render(_windowWidth - 30, _windowHeight / 2 - m_player2Paddle->GetHeight() / 2);

	m_computerScore->Render(_windowWidth / 4, 10);
	m_playerScore->Render(_windowWidth - _windowWidth / 4, 10);
}

Texture& TextureManager::GetBallTexture() const
{
	return *m_ball;
}

Texture& TextureManager::GetPlayerPaddleTexture() const
{
	return *m_playerPaddle;
}

Texture& TextureManager::GetComputerPaddleTexture() const
{
	return *m_computerPaddle;
}
