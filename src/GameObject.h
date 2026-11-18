#pragma once
#include "game.h"

class GameObject
{
public: 
	virtual ~GameObject() {};

	virtual void render() const = 0;
	virtual bool update(float delta) = 0;
	virtual void save(std::ostream& out) = 0;
	virtual void load(std::istream& in) = 0;

protected:
	GameObject(Game* gm) : _gm(gm) {};

	Game* _gm;
};
