#include "CurackHaus.h"

CurackHaus::CurackHaus()
{

}

void CurackHaus::LoadContent(ResourceManager& resourceManager)
{
	PlayerShip::LoadContent(resourceManager);

	//Change Texture
	//m_pTexture = resourceManager.Load<Texture>("Textures\\CurackHaus.png"); Change to an actual texture when finished

	//Plan: Spawn crack rocks that make this guy faster and more powerful, but if he doesn't pick them up he'll move and fire flower
}