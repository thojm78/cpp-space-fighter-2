#pragma once

#include "PlayerShip.h"

class CurackHaus : public PlayerShip
{
public:
	CurackHaus();
	~CurackHaus() {}

	virtual void Update(const GameTime& gameTime) override;
	virtual void LoadContent(ResourceManager& resourceManager) override;

	void IncrementKillCount();
	void GetHigh();


	int GetKillCount() const { return m_killCount; }
	bool IsHighActive() const { return m_isHigh; }

private:
	int m_killCount = 0;

	bool m_isHigh = false;
	float m_highTimer = 0;

	//Original Values
	float m_originalSpeed = 0;
	float m_originalFireRate = 0;
};