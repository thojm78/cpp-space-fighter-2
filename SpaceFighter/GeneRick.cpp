#include "GeneRick.h"

GeneRick::GeneRick()
{

}

void GeneRick::LoadContent(ResourceManager& resourceManager)
{
	PlayerShip::LoadContent(resourceManager);

	//Set up textures
	m_pTexture = resourceManager.Load<Texture>("Textures\\PlayerShip.png"); //Texture for character
	m_pNormalTexture = m_pTexture;
	m_pShieldTexture = resourceManager.Load<Texture>("Textures\\PlayerShipForcefield.png"); //Used when shield active
}

void GeneRick::Update(const GameTime& gameTime)
{
	PlayerShip::Update(gameTime);
	//When shield active, activate timer
	if (m_shield)
	{
		m_shieldTimer -= (float)gameTime.GetElapsedTime();
		if (m_shieldTimer <= 0)
		{
			m_shield = false;
			m_pTexture = m_pNormalTexture;
		}
	}
}

void GeneRick::IncrementKillCount()
{
	//Only count if shield not up
	if (!m_shield) { m_killCount++; }
}

void GeneRick::ActivateShield()
{
	//Enable shield ability
	m_shield = true;
	m_shieldTimer = 5.0f;
	m_killCount = 0;

	m_pTexture = m_pShieldTexture; //Switch player visual
}

void GeneRick::Hit(const float damage)
{
	//If shield true, block damage
	//Otherwise, take damage as usual
	if (m_shield) return;
	Ship::Hit(damage);
}