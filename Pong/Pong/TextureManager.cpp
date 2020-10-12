#include "TextureManager.h"

#include <assert.h> 

#include "Texture.h"
#include "GameManager.h"

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
	m_player1Paddle = new Texture();
	m_player2Paddle = new Texture();
	m_player1Score = new Texture();
	m_player2Score = new Texture();

}

void TextureManager::Destroy()
{
	delete m_ball;
	delete m_player1Paddle;
	delete m_player2Paddle;
	delete m_player1Score;
	delete m_player2Score;
}

void TextureManager::LoadTextures()
{
	m_ball->LoadFromFile("Textures/Ball.png");
}

void TextureManager::RenderTextures()
{
	m_ball->Render(0, 0);
}
