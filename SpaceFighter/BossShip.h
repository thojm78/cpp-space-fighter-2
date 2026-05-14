
#pragma once
#include "EnemyShip.h"

/** @brief Represents an enemy ship that is biological in nature. */
class BossShip : public EnemyShip
{

public:

	/** @brief Creates a new instance of BioEnemyShip. */
	BossShip();
	virtual ~BossShip() {}
	/** @brief Sets the texture that will be used to render the enemy ship.
		@param pTexture A pointer to the texture. */
	virtual void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

	/** Create + initialize a boss with common setup to make Level code simpler. */
	static BossShip* Create(Texture* pTexture, Level* level, const Vector2& position, float delay);

	//for shooting
	static BossShip* Create(Texture* pTexture, Level* level, const Vector2& position, float delay, std::vector<Projectile*>* pProjectilePool);
	void SetFireInterval(float seconds) { m_fireInterval = seconds; }

	/** @brief Updates the enemy ship.
		@param gameTime A reference to the game time object. */
	virtual void Update(const GameTime& gameTime);

	/** @brief Draws the enemy ship.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch);

	/** Returns the currently set texture (may be nullptr). */
	Texture* GetTexture() const { return m_pTexture; }



private:
	float m_fireTimer = 0.0f;
	float m_fireInterval = 0.1f;

	Texture* m_pTexture = nullptr;
};