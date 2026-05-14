#include "CurackHaus.h"
#include "Blaster.h"

CurackHaus::CurackHaus() {}

void CurackHaus::LoadContent(ResourceManager& resourceManager) {
    PlayerShip::LoadContent(resourceManager);
    m_pTexture = resourceManager.Load<Texture>("Textures\\PlayerShipCrackHaus.png"); //Player ship
}

void CurackHaus::IncrementKillCount() {
    if (!m_isHigh) {m_killCount++;} //Increase special ability when it is not active
}

void CurackHaus::GetHigh() {
    m_killCount = 0;
    m_isHigh = true;
    m_highTimer = 5.0f; //Boost lasts for 5 seconds
    m_speed = 3000.0f; //Speed Boost

    // Find player's equipped weapon
    Weapon* pWeapon = GetWeapon("Main Blaster");
    if (pWeapon) {
        Blaster* pBlaster = dynamic_cast<Blaster*>(pWeapon);
        if (pBlaster) {
            pBlaster->SetCooldownSeconds(0.005f); //Cooldown reduction 
        }
    }
}

void CurackHaus::Update(const GameTime& gameTime) {
    PlayerShip::Update(gameTime);

    if (m_isHigh) {
        m_highTimer -= (float)gameTime.GetElapsedTime(); //If ability is active, reduce the remaining ability time

        //Revoke abilities, set back to normal
        if (m_highTimer <= 0) {
            m_isHigh = false;
            m_speed = 300.0f;

            Weapon* pWeapon = GetWeapon("Main Blaster");
            if (pWeapon) {
                Blaster* pBlaster = dynamic_cast<Blaster*>(pWeapon);
                if (pBlaster) {
                    pBlaster->SetCooldownSeconds(0.35f);
                }
            }
        }
    }
}