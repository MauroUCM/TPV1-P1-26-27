#pragma once
#include "SceneObject.h"

class MobileObject : public SceneObject
{
public:
	MobileObject(Game* gm, Texture* text);
	MobileObject(Game* gm, Texture* text, Rectangle* rec, Vector2D<float> vel = { 0.0f, 0.0f });

	virtual void render() const override = 0;
	bool update(float delta) override;

	virtual void save(std::ostream& out) override;
	virtual void load(std::istream& in) override;

protected:
	Vector2D<float> _vel;
};
