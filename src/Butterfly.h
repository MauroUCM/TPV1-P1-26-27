#pragma once
#include "MobileObject.h"

constexpr float BTF_SIZE = 50.0f;
constexpr float FALL_SPEED = 2.0f;
constexpr float BTF_MAX_SPEED = 3.0f;
constexpr float BTF_MIN_SPEED = 1.0f;
constexpr int BTF_PENALTY = -10;

enum BtflyAnimnState {
	MOVING_LEFT = 0,
	MOVING_RIGHT,
	TURNING_LEFT,
	TURNING_RIGHT
};

class Butterfly : public MobileObject
{
public:
	Butterfly(Game* game, Texture* text, Vector2D<float> pos);

	void render() const override;
	bool update(float delta) override;
	bool hit(const Rectangle& obj) override;

private:
	void changeDirRnd();
	
	BtflyAnimnState _animState = MOVING_LEFT;
	float _speed;
	float _nextDirChange;

	Uint16 _animFrame = 0;
	bool _alive = true;
	Uint16 _timeSncLastFrame = 0;
	Uint16 _timeSncLastDirChng = 0;
};
