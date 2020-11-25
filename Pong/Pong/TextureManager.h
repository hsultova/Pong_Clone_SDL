#pragma once
#include "Texture.h"

class TextureManager
{
public:
	static TextureManager* Get();

	static void RegisterInstance(TextureManager* _instance);
	static void UnregisterInstance(TextureManager* _instance);

	void Initialize(SDL_Renderer* _renderer);
	void Destroy();

	void LoadTextures();

	Texture& GetBall() const;
	Texture& GetPlayerPaddle() const;
	Texture& GetComputerPaddle() const;
	Texture& GetComputerScore() const;
	Texture& GetPlayerScore() const;
	Texture& GetSingleplayerMode() const;
	Texture& GetMultiplayerMode() const;

private:
	static TextureManager* s_instance;

	Texture* m_ball;
	Texture* m_computerPaddle;
	Texture* m_playerPaddle;
	Texture* m_computerScore;
	Texture* m_playerScore;
	Texture* m_singleplayerMode;
	Texture* m_multiplayerMode;
	//Texture* m_onlinemultiplayerMode;
};

