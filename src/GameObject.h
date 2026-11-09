#pragma once
#include "game.h"

class GameObject
{
public: 
	virtual void render() const = 0;
	virtual bool update(float delta) = 0;

protected:
	GameObject(Game* gm) {};

	Game* _gm;
};
