#include "CharacterSelect.h"
#include "GameplayScreen.h"
#include "GeneRick.h"
#include "CurackHaus.h"
#include "SaiKo.h"


CharacterSelectScreen::CharacterSelectScreen()
{
    SetTransitionInTime(1);
    SetTransitionOutTime(0.5f);
    Show();
}

void CharacterSelectScreen::LoadContent(ResourceManager& resourceManager)
{
    m_pBackgroundTexture = resourceManager.Load<Texture>("Textures\\Placeholder.png");

    // Font
    Font::SetLoadSize(24, true);
    m_pFont = resourceManager.Load<Font>("Fonts\\arial.ttf");

    RefreshCharacterMenu(resourceManager);
}

void CharacterSelectScreen::RefreshCharacterMenu(ResourceManager& resourceManager)
{
	//Clear existing menu items
auto& items = GetMenuItems();
    for (MenuItem* pItem : items)
    {
        delete pItem; 
    }
    items.clear();

	//Load the portrait for the currently selected character
    m_pPortraitTexture = resourceManager.Load<Texture>(m_portraitPaths[m_selectedCharacterIndex]);

    //Navigation Buttons
    float screenWidth = (float)Game::GetScreenWidth();

    MenuItem* pBackItem = new MenuItem("Prev");
    pBackItem->SetPosition(Vector2(screenWidth - 150, 50));
    pBackItem->SetFont(m_pFont);
    pBackItem->SetOnSelect([this, &resourceManager]()
        {
            m_selectedCharacterIndex = (m_selectedCharacterIndex - 1 + m_characterCount) % m_characterCount;
            RefreshCharacterMenu(resourceManager);
        });
    AddMenuItem(pBackItem);

	MenuItem* pNextItem = new MenuItem("Next");
	pNextItem->SetPosition(Vector2(screenWidth - 150, 100));
	pNextItem->SetFont(m_pFont);
	pNextItem->SetOnSelect([this, &resourceManager]()
		{
			m_selectedCharacterIndex = (m_selectedCharacterIndex + 1) % m_characterCount;
			RefreshCharacterMenu(resourceManager);
		});
	AddMenuItem(pNextItem);

    //Selection Button
	std::string names[3] = { "Gene Rick", "Curack Haus", "Sai Ko" };
    MenuItem* pSelect = new MenuItem("Select  " + names[m_selectedCharacterIndex]);

    //Position at the bottom center
	pSelect->SetPosition(Vector2(Game::GetScreenCenter().X - 100, Game::GetScreenHeight() - 100));
    pSelect->SetFont(m_pFont);
    pSelect->SetOnSelect([this]()
        {
            SetOnRemove([this]() {
                // Pass 0 for the first level, and your selection for the character
                AddScreen(new GameplayScreen(0, m_selectedCharacterIndex));
                });
            Exit();
        });
    AddMenuItem(pSelect);
}

void CharacterSelectScreen::Draw(SpriteBatch& spriteBatch)
{
    spriteBatch.Begin();

	if (m_pPortraitTexture)
	{
        float scaleX = (float)Game::GetScreenWidth() / m_pPortraitTexture->GetWidth();
		float scaleY = (float)Game::GetScreenHeight() / m_pPortraitTexture->GetHeight();
        Vector2 scale(scaleX, scaleY);

        spriteBatch.Draw(m_pPortraitTexture,Vector2::ZERO,Color::WHITE * GetAlpha(),Vector2::ZERO, scale,0.0f, 0.0f);
	}

    MenuScreen::Draw(spriteBatch);
    spriteBatch.End();
}

void CharacterSelectScreen::Update(const GameTime& gameTime)
{
    float alpha = GetAlpha();

    //Go through all items to update visual state
    for (MenuItem* pItem : GetMenuItems())
    {
        pItem->SetAlpha(alpha);

        //Check which is being hovered
        if (pItem->IsSelected())
        {
            pItem->SetColor(Color::WHITE); //Hover Color
        }
        else
        {
            pItem->SetColor(Color::BLUE); //Default Color
        }
    }

    MenuScreen::Update(gameTime);
}