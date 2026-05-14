#pragma once

#include "KatanaEngine.h"
#include "PlayerShip.h"

using namespace KatanaEngine;

class CharacterSelectScreen : public MenuScreen
{
public:
	CharacterSelectScreen();
	virtual ~CharacterSelectScreen() {}

	virtual void LoadContent(ResourceManager& resourceManager) override;
	virtual void Update(const GameTime& gameTime) override;
	virtual void Draw(SpriteBatch& spriteBatch) override;

private:
	void RefreshCharacterMenu(ResourceManager& resourceManager);

	Texture* m_pBackgroundTexture = nullptr;
	Texture* m_pPortraitTexture = nullptr;
	Texture* m_pPlayerShipTexture = nullptr;
	Font* m_pFont = nullptr;

	int m_selectedCharacterIndex = 0;
	const int m_characterCount = 3;


	std::string m_portraitPaths[3] = { "Textures\\GeneRickSelect.png", "Textures\\CurackHouseSelect.png", "Textures\\SaiKoCharacterSelect.png" };


};