
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "Level.h"
#include "Level01.h"
#include "Blaster.h"
#include "GeneRick.h"
#include "CurackHaus.h"
#include "SaiKo.h"

GameplayScreen::GameplayScreen(int levelIndex, int characterIndex)
	: m_levelIndex(levelIndex), m_characterIndex(characterIndex)
{
	SetTransitionInTime(1);
	SetTransitionOutTime(3);

	SetOnRemove([this](){ AddScreen(new MainMenuScreen()); });

	Show();
}

void GameplayScreen::LoadContent(ResourceManager& resourceManager)
{
	m_pResourceManager = &resourceManager;
	LoadLevel(m_levelIndex);

	PlayerShip* pPlayer = nullptr;

	switch (m_characterIndex)
	{
	case 0: pPlayer = new GeneRick(); break;
	case 1: pPlayer = new CurackHaus(); break;
	case 2: pPlayer = new SaiKo(); break;
	default: pPlayer = new PlayerShip(); break;
	}

	if (pPlayer && m_pLevel)
	{
		pPlayer->LoadContent(resourceManager);
		Blaster* pBlaster = new Blaster("Main Blaster");
		pBlaster->SetProjectilePool(m_pLevel->GetProjectilePool());
		pPlayer->AttachItem(pBlaster, Vector2::UNIT_Y * -20);

		m_pLevel->SetPlayer(pPlayer);
		m_pLevel->AddGameObject(pPlayer);
		pPlayer->Activate();
	}
}

void GameplayScreen::LoadLevel(const int levelIndex)
{
	if (m_pLevel) delete m_pLevel;

	switch (levelIndex)
	{
	case 0: m_pLevel = new Level01(); break;
	}

	m_pLevel->SetGameplayScreen(this);
	m_pLevel->LoadContent(*m_pResourceManager);
}

void GameplayScreen::HandleInput(const InputState& input)
{
	m_pLevel->HandleInput(input);
}

void GameplayScreen::Update(const GameTime& gameTime)
{
	m_pLevel->Update(gameTime);
}

void GameplayScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();

	m_pLevel->Draw(spriteBatch);

	spriteBatch.End();
}
