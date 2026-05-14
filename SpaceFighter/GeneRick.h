#pragma once

#include "PlayerShip.h"

class GeneRick : public PlayerShip
{
public:
    GeneRick();
    virtual void Update(const GameTime& gameTime) override;
    //virtual void Draw(SpriteBatch& spriteBatch) override;
    virtual void Hit(const float damage) override;
    virtual void LoadContent(ResourceManager& resourceManager) override;
    virtual ~GeneRick() {}

    void IncrementKillCount();
    void ActivateShield();
    int GetKillCount() const { return m_killCount; }
    bool IsShieldActive() const { return m_shield; }


private:
    int m_killCount = 0;
    bool m_shield = false;
    float m_shieldTimer = 0;

    Texture* m_pNormalTexture = nullptr;
    Texture* m_pShieldTexture = nullptr;
};