#include "Level02.h"
#include "BioEnemyShip.h"
#include "BossShip.h"


void Level02::LoadContent(ResourceManager& resourceManager)
{
	// Setup enemy ships
	Texture* pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");
	Texture* BpTexture = resourceManager.Load<Texture>("Textures\\Ravager.webp");

	const int COUNT = 22;
	const int BCOUNT = 3;

	double BxPositions[BCOUNT] = {
		0.50, 0.75, 0.25
	};
	double Bdelays[BCOUNT] = {
		0.25, 5.00, 8.00
	};


	double xPositions[COUNT] =
	{
		0.25, 0.2, 0.3,
		0.75, 0.8, 0.7,
		0.3, 0.25, 0.35, 0.2, 0.4,
		0.7, 0.75, 0.65, 0.8, 0.6,
		0.5, 0.4, 0.6, 0.45, 0.55, .6
	};

	double delays[COUNT] =
	{
		0.0, 0.25, 0.25,
		3.0, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.5, 0.3, 0.3, 0.3, 0.3, 0.3
	};

	float delay = 3.0f; // start delay
	float Bdelay = 0.1f;
	Vector2 position;
	Vector2 Bposition;

	for (int i = 0; i < COUNT; i++)
	{
		delay += delays[i];
		position.Set(xPositions[i] * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

		BioEnemyShip* pEnemy = new BioEnemyShip();
		pEnemy->SetTexture(pTexture);
		pEnemy->SetCurrentLevel(this);
		pEnemy->Initialize(position, (float)delay);
		AddGameObject(pEnemy);


	}
	if (!BpTexture)
	{
		std::cout << "Failed to load boss texture." << std::endl;
	}
	else
	{
		for (int j = 0; j < BCOUNT; ++j)
		{
			Bdelay += static_cast<float>(Bdelays[j]);
			Vector2 Bposition;
			Bposition.Set(static_cast<float>(BxPositions[j]) * Game::GetScreenWidth(), -BpTexture->GetCenter().Y);


			BossShip* pBoss = BossShip::Create(BpTexture, this, Bposition, Bdelay, GetProjectilePool());
			AddGameObject(pBoss);
			std::cout << "Added Boss at pos(" << Bposition.X << "," << Bposition.Y << ") delay=" << Bdelay << " index=" << pBoss->GetIndex() << std::endl;
		}
	}


	SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground01.png"));

	Level::LoadContent(resourceManager);
}