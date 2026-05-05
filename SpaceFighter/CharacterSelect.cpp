#include "CharacterSelect.h"
#include "GameplayScreen.h"


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
    Font* pFont = resourceManager.Load<Font>("Fonts\\arial.ttf");

    // Define Characters
    const int CharacterCount = 3;
    std::string names[CharacterCount] = { "Gene Rick", "Curack Haus", "Sai Ko" };

    SetDisplayCount(CharacterCount);

    // FIX 1: Added 'int i = 0' (Your version had 'int = 0')
    for (int i = 0; i < CharacterCount; i++)
    {
        MenuItem* pItem = new MenuItem(names[i]);
        pItem->SetPosition(Vector2(Game::GetScreenCenter().X - 100, 200 + 60 * i));
        pItem->SetFont(pFont);
        pItem->SetColor(Color::BLUE);
        pItem->SetSelected(i == 0);

        // When character is selected, move to gameplay
        pItem->SetOnSelect([this, i]() {
            SetOnRemove([this, i]() {
                AddScreen(new GameplayScreen());
                });
            Exit();
            });

        AddMenuItem(pItem);
    } 
}

void CharacterSelectScreen::Update(const GameTime& gameTime)
{
    float alpha = GetAlpha();

    for (MenuItem* pItem : GetMenuItems())
    {
        pItem->SetAlpha(alpha);
        bool isSelected = pItem->IsSelected();
        pItem->SetColor(isSelected ? Color::YELLOW : Color::BLUE);
    }

    MenuScreen::Update(gameTime);
}

void CharacterSelectScreen::Draw(SpriteBatch& spriteBatch)
{
    spriteBatch.Begin();

    if (m_pBackgroundTexture)
    {
        spriteBatch.Draw(m_pBackgroundTexture, Vector2::ZERO, Color::WHITE * GetAlpha());
    }

    MenuScreen::Draw(spriteBatch);

    spriteBatch.End();

}