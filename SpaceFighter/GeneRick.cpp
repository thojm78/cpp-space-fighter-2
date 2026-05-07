#include "GeneRick.h"

GeneRick::GeneRick()
{

}

void GeneRick::LoadContent(ResourceManager& resourceManager)
{
	PlayerShip::LoadContent(resourceManager);

	//Change Texture
	//m_pTexture = resourceManager.Load<Texture>("Textures\\GeneRick.png"); Change to an actual texture when finished

	//Plan: Give this guy a forcefield that can activate
}