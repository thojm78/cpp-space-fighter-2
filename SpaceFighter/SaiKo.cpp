#include "SaiKo.h"

SaiKo::SaiKo()
{

}

void SaiKo::LoadContent(ResourceManager& resourceManager)
{
	PlayerShip::LoadContent(resourceManager);

	//Change Texture
	m_pTexture = resourceManager.Load<Texture>("Textures\\PlayerShipSaiKo.png");

	//Plan: When enough kills are scored, activate a bomb that just kills everyone
}