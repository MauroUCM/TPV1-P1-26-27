#pragma once
#include "MobileObject.h"

constexpr int BALLOON_SIZE = 150;

class Balloon : public MobileObject
{
public:
	Balloon(Game* gm, Vector2D<float> pos, float vel, Texture* text, int color = 0);

	void render() const override;
	bool update(float delta) override;

	bool hit(const Rectangle& obj);

private:
	// variables
	int _color;

	// variables internas
	int _animationState;
	bool _alive = true;
};

