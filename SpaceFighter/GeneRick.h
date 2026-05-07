#pragma once

#include "PlayerShip.h"

class GeneRick : public PlayerShip
{
public:
    GeneRick();
    virtual ~GeneRick() {}

    virtual void LoadContent(ResourceManager& resourceManager) override;
};