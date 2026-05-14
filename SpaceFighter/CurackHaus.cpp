#include "CurackHaus.h"

CurackHaus::CurackHaus()
{

}

void CurackHaus::LoadContent(ResourceManager& resourceManager)
{
    PlayerShip::LoadContent(resourceManager);
    m_pTexture = resourceManager.Load<Texture>("Textures\\PlayerShipCrackHaus.png");

    //Put crack rocks in that modify stats
}