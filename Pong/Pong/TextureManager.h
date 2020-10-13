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
	void RenderTextures(int _windowWidth, int _windowHeight);

	Texture& GetBallTexture() const;
	Texture* GetPlayerPaddleTexture() const;
	Texture* GetComputerPaddleTexture() const;

private:
	static TextureManager* s_instance;

	Texture* m_ball;
	Texture* m_computerPaddle;
	Texture* m_playerPaddle;
	Texture* m_computerScore;
	Texture* m_playerScore;
};

