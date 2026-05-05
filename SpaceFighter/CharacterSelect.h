#pragma once

#include "KatanaEngine.h"

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
	Texture* m_pBackgroundTexture = nullptr;
	int m_selectedCharacterIndex = 0;
};