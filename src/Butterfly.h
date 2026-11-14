#pragma once
#include "MobileObject.h"

constexpr float BTF_SIZE = 50.0f;
constexpr float BTF_DEAD_SPEED = 50.0f;
constexpr int BTF_MAX_SPEED = 50.0f;
constexpr int BTF_MIN_SPEED = 5.0f;

enum BtflyAnimnState {
	MOVING_LEFT = 0,
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
	bool hit(const Rectangle& obj) override;

private:
	void changeDirRnd();

	BtflyAnimnState _animState = MOVING_LEFT;
	float _speed;

	int _animFrame = 0;
	bool _alive = true;
	int _timeSncLastFrame = 0;


};
