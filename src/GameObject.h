#pragma once
#include "game.h"


class GameObject
{
public: 
	GameObject(Game* gm);

	virtual void render() const = 0;
	virtual void update() = 0;

protected:
	Game* _gm;
};
