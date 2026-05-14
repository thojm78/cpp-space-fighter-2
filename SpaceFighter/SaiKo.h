#pragma once

#include "PlayerShip.h"

class SaiKo : public PlayerShip
{
public:
	SaiKo();
	virtual ~SaiKo() {}
	virtual void LoadContent(ResourceManager& resourceManager) override;

	void IncrementKillCount();
	void ActivateNuke();
	int GetKillCount() const { return m_killCount; }

private:
	int m_killCount = 0;
};