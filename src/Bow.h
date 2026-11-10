#pragma once
#include "MobileObject.h"

constexpr int BOW_SIZE = 100;

class Bow : public MobileObject
{
public:
	Bow(Game* game, Vector2D<float> pos, float speed, Texture* text);

	void render() const override;
	bool update(float delta) override;
	void handleEvent(const SDL_Event& event);

private:
	void shoot();

	float _speed;
	bool _armed;
};

