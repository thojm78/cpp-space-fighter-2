#pragma once

#include "PlayerShip.h"

class SaiKo : public PlayerShip
{
public:
	SaiKo();
	virtual ~SaiKo() {}

	virtual void LoadContent(ResourceManager& resourceManager) override;
};