#pragma once

#include "PlayerShip.h"

class CurackHaus : public PlayerShip
{
public:
	CurackHaus();
	~CurackHaus() {}

	virtual void LoadContent(ResourceManager& resourceManager) override;
};