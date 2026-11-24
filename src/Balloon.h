#pragma once
#include "MobileObject.h"

constexpr int BALLOON_SIZE = 100;

class Balloon : public MobileObject
{
public:
	Balloon(Game* gm);
	Balloon(Game* gm, Vector2D<float> pos, float speed, int color = 0);

	void render() const override;
	bool update(float delta) override;

	virtual void save(std::ostream& out) override;
	virtual void load(std::istream& in) override;

	bool hit(const Rectangle& obj) override;

private:
	// variables
	int _color;

	// variables internas
	int _animationState = 0;
	bool _alive = true;
	int _timeSncLastFrame = 0;
};

