#pragma once
#include "SceneObject.h"

class MobileObject : public SceneObject
{
public:
	MobileObject(Game* gm, Texture* text, Rectangle* rec, Vector2D<float> vel);

	virtual void render() const override = 0;
	bool update(float delta) override;

protected:
	Vector2D<float> _vel;
};
