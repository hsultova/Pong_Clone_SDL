#include <stdio.h>

#include "GameManager.h"
#include "TextureManager.h"

int main(int argc, char* args[])
{
	GameManager* gameManager = &GameManager();
	GameManager::RegisterInstance(gameManager);

	if (!GameManager::Get()->Initialize())
	{
		printf("Failed to initialize!\n");
		return -1;
	}

	TextureManager* textureManager = &TextureManager();
	TextureManager::RegisterInstance(textureManager);
	textureManager->Initialize(gameManager->GetRenderer());

	textureManager->LoadTextures();
	gameManager->PlayGame();

	textureManager->Destroy();
	TextureManager::UnregisterInstance(textureManager);

	gameManager->Destroy();
	GameManager::UnregisterInstance(gameManager);

	return 0;
}