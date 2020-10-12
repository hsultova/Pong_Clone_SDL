#include <stdio.h>

#include "GameManager.h"
#include "TextureManager.h"

int main(int argc, char* args[])
{
	GameManager* gameManager = &GameManager();
	GameManager::RegisterInstance(gameManager);

	TextureManager* textureManager = &TextureManager();
	TextureManager::RegisterInstance(textureManager);
	textureManager->Initialize();

	if (!GameManager::Get()->Initialize())
	{
		printf("Failed to initialize!\n");
		return -1;
	}

	textureManager->LoadTextures();
	gameManager->PlayGame();

	gameManager->Destroy();
	GameManager::UnregisterInstance(gameManager);

	textureManager->Destroy();
	TextureManager::UnregisterInstance(textureManager);

	return 0;
}