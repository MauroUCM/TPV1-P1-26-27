#pragma once
#include "MobileObject.h"

constexpr int BUTTERFLY_SIZE = 20;

enum BtflyAnimnState {
	MOVING_LEFT = 1,
	MOVING_RIGHT,
	TURNING_LEFT,
	TURNING_RIGHT
};

class Butterfly : public MobileObject
{
public:
	Butterfly(Game* game, Texture* text);

	void render() const override;
	bool update(float delta) override;

private:
	void changeSpeedRnd();

	BtflyAnimnState animState;
	int animFrame = 0;

};
