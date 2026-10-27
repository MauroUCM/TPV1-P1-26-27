#pragma once
#include "SceneObject.h"

class MobileObject : public SceneObject
{
public:
	MobileObject(Game* gm, Texture* text, Rectangle* rec, Vector2D<float> vel);

	virtual void render() const override = 0;
	virtual void update() override = 0;

protected:
	Vector2D<float> _vel;
};
