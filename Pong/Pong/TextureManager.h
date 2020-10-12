#pragma once
#include "Texture.h"

class TextureManager
{
public:
	static TextureManager* Get();

	static void RegisterInstance(TextureManager* _instance);
	static void UnregisterInstance(TextureManager* _instance);

	void Initialize();
	void Destroy();

	void LoadTextures();
	void RenderTextures();

private:
	static TextureManager* s_instance;

	Texture* m_ball;
	Texture* m_player1Paddle;
	Texture* m_player2Paddle;
	Texture* m_player1Score;
	Texture* m_player2Score;
};

