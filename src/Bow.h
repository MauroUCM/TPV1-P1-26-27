#pragma once
#include "MobileObject.h"

constexpr int BOW_SIZE = 100;

class Bow : public MobileObject
{
public:
	Bow(Game* gm);
	Bow(Game* game, Vector2D<float> pos, float speed);

	void render() const override;
	bool update(float delta) override;
	void handleEvent(const SDL_Event& event);

	virtual void save(std::ostream& out) override;
	virtual void load(std::istream& in) override;

private:
	void shoot();

	float _speed;
	bool _armed;
};

