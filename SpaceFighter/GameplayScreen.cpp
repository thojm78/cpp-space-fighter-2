
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "MenuItem.h"
#include "Level.h"
#include "Level01.h"
#include "Level02.h"
#include "Blaster.h"
#include "GeneRick.h"
#include "CurackHaus.h"
#include "SaiKo.h"

GameplayScreen::GameplayScreen(int levelIndex, int characterIndex)
	: m_levelIndex(levelIndex), m_characterIndex(characterIndex)
{
	SetTransitionInTime(1);
	SetTransitionOutTime(3);

	SetOnRemove([this]() { AddScreen(new MainMenuScreen()); });

	Show();
}

void GameplayScreen::LoadContent(ResourceManager& resourceManager)
{
	m_pResourceManager = &resourceManager;
	LoadLevel(m_levelIndex);

	PlayerShip* pPlayer = nullptr;

	//Create selected player on characters choice
	switch (m_characterIndex)
	{
	case 0: pPlayer = new GeneRick(); break;
	case 1: pPlayer = new CurackHaus(); break;
	case 2: pPlayer = new SaiKo(); break;
	default: pPlayer = new PlayerShip(); break;
	}

	if (pPlayer && m_pLevel)
	{
		//Set up level and player
		pPlayer->LoadContent(resourceManager);
		Blaster* pBlaster = new Blaster("Main Blaster");
		pBlaster->SetProjectilePool(m_pLevel->GetProjectilePool());
		pPlayer->AttachItem(pBlaster, Vector2::UNIT_Y * -20);

		m_pLevel->SetPlayer(pPlayer);
		m_pLevel->AddGameObject(pPlayer);
		pPlayer->Activate();
	}

	//m_pShieldReadyTexture = resourceManager.Load<Texture>("Textures\\AbilityReady.png");

}

void GameplayScreen::LoadLevel(const int levelIndex)
{
	if (m_pLevel) delete m_pLevel;

	switch (levelIndex)
	{
	case 0: m_pLevel = new Level02(); break;
	}

	m_pLevel->SetGameplayScreen(this);
	m_pLevel->LoadContent(*m_pResourceManager);
}

void GameplayScreen::HandleInput(const InputState& input)
{
	m_pLevel->HandleInput(input);

	//Track kills and activate special abilities for each character
	//Check if special ability isn't already active
	GeneRick* pGeneRick = dynamic_cast<GeneRick*>(m_pLevel->GetPlayer());
	if (pGeneRick && pGeneRick->GetKillCount() >= 3 && !pGeneRick->IsShieldActive())
	{
		if (input.IsNewKeyPress((Key)67)) //67 is the enter key (SIX-SEVEN!!!)
		{
			pGeneRick->ActivateShield();
		}
	}

	CurackHaus* pCurackHaus = dynamic_cast<CurackHaus*>(m_pLevel->GetPlayer());
	if (pCurackHaus)
	{
		if (pCurackHaus->GetKillCount() >= 3 && !pCurackHaus->IsHighActive())
		{
			if (input.IsNewKeyPress((Key)67))
			{
				pCurackHaus->GetHigh();
			}
		}
	}

	SaiKo* pSaiKo = dynamic_cast<SaiKo*>(m_pLevel->GetPlayer());
	if (pSaiKo && pSaiKo->GetKillCount() >= 3) {
		if (input.IsNewKeyPress((Key)67)) {
			pSaiKo->ActivateNuke();
		}
	}
}

void GameplayScreen::Update(const GameTime& gameTime)
{
	m_pLevel->Update(gameTime);
}

void GameplayScreen::Draw(SpriteBatch& spriteBatch) {
	spriteBatch.Begin();
	m_pLevel->Draw(spriteBatch);
	GeneRick* pGeneRick = dynamic_cast<GeneRick*>(m_pLevel->GetPlayer());

	if (pGeneRick && pGeneRick->GetKillCount() >= 3 && !pGeneRick->IsShieldActive()) {
		if (m_pShieldReadyTexture != nullptr) {
			Vector2 pos = Vector2(Game::GetScreenWidth() / 2, 500);
			//spriteBatch.Draw(m_pShieldReadyTexture, pos, Color::WHITE, Vector2::ZERO); Doesn't work for some reason
		}
	}
	spriteBatch.End();
}