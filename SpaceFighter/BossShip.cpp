#include "BossShip.h"
#include "Level.h"
#include "Blaster.h"
#include "TriggerType.h"
#include <iostream>


BossShip::BossShip()
{
	SetSpeed(100);
	SetMaxHitPoints(5);
	SetCollisionRadius(135);

	m_fireTimer = 0.0f;
	m_fireInterval = 0.1f;
}

BossShip* BossShip::Create(Texture* pTexture, Level* level, const Vector2& position, float delay)
{
	BossShip* boss = new BossShip();
	boss->SetTexture(pTexture);
	if (level) boss->SetCurrentLevel(level);
	boss->Initialize(position, delay);
	return boss;
}

BossShip* BossShip::Create(Texture* pTexture, Level* level, const Vector2& position, float delay, std::vector<Projectile*>* pProjectilePool)
{
	BossShip* boss = Create(pTexture, level, position, delay);
	if (pProjectilePool)
	{
		Blaster* pBlaster = new Blaster("Boss Blaster");
		pBlaster->SetAttachedToPlayer(false);        // mark projectiles as enemy
		pBlaster->SetProjectilePool(pProjectilePool);
		// attach at boss origin; tweak offset if you want bullets to spawn from a gun point
		Vector2 offset = Vector2::ZERO;
		boss->AttachItem(pBlaster, offset);
		// optional: tune boss fire interval
		boss->SetFireInterval(0.8f);
	}
	return boss;
}

void BossShip::Update(const GameTime& gameTime)
{
	if (!IsActive())
	{
		EnemyShip::Update(gameTime);
		return;
	}

	const float elapsed = gameTime.GetElapsedTime();
	const float total = static_cast<float>(gameTime.GetTotalTime());

	// defensive: if time is not progressing, skip movement
	if (elapsed > 0.0f)
	{
		// horizontal sinusoidal wave (per-index phase)
		const float phase = total * Math::PI + static_cast<float>(GetIndex());
		const float wave = static_cast<float>(sin(phase));

		const float speed = GetSpeed();
		const float dx = wave * speed * elapsed * 2.0f;
		const float dy = speed * elapsed;

		TranslatePosition(dx, dy);

		m_fireTimer -= elapsed;
		if (m_fireTimer <= 0.0f)
		{
			// Fire primary weapon(s) attached to this ship
			FireWeapons(TriggerType::Primary);
			m_fireTimer = m_fireInterval;
		}
	}


	EnemyShip::Update(gameTime);
}


void BossShip::Draw(SpriteBatch& spriteBatch)
{
	if (!IsActive()) return;

	if (!m_pTexture)
	{
		std::cout << "Boss Draw skipped: null texture\n";
		return;
	}
	const Level* level = GetCurrentLevel();
	if (!level)
	{
		std::cout << "Boss Draw skipped: null level\n";
		return;
	}

	float alpha = level->GetAlpha();
	if (alpha < 0.0f) alpha = 0.0f;
	else if (alpha > 1.0f) alpha = 1.0f;

	const float rotation = 0.0f;
	const float layerDepth = 0.0f;
	spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, rotation, layerDepth);
}