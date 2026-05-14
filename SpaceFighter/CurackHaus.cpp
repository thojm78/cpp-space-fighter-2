#include "CurackHaus.h"

CurackHaus::CurackHaus()
{

}

void CurackHaus::LoadContent(ResourceManager& resourceManager)
{
	PlayerShip::LoadContent(resourceManager);

	m_pTexture = resourceManager.Load<Texture>("Textures\\PlayerShipCrackHaus.png");

	//Plan: Spawn crack rocks that make this guy faster and more powerful, but if he doesn't pick them up he'll move and fire flower
}