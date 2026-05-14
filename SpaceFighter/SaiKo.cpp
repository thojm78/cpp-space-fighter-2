#include "SaiKo.h"
#include "EnemyShip.h"
#include "Level.h"

SaiKo::SaiKo()
{

}

void SaiKo::LoadContent(ResourceManager& resourceManager)
{
	PlayerShip::LoadContent(resourceManager);

	//Change Texture
	m_pTexture = resourceManager.Load<Texture>("Textures\\PlayerShipSaiKo.png"); //Load SaiKo's sprite
}

void SaiKo::IncrementKillCount()
{
	m_killCount++; //Count kills always
}

void SaiKo::ActivateNuke() {

    if (m_killCount < 3) return;
    m_killCount = 0; // Reset the count

    //Retrieve active level and its objects
    Level* pLevel = (Level*)GameObject::GetCurrentLevel();
    if (!pLevel) return;

    std::vector<GameObject*>& objects = pLevel->GetGameObjects();

    //Look for enemies
    for (GameObject* pObject : objects) {
        // Check for active enemies and kill'em
        if (pObject && pObject->IsActive() && pObject->HasMask(CollisionType::Enemy)) {
            Ship* pEnemy = dynamic_cast<Ship*>(pObject);
            if (pEnemy) {
                pEnemy->Hit(9999.0f); // Nuke damage
                pLevel->SpawnExplosion(pEnemy); // Visual chaos
            }
        }
    }
}