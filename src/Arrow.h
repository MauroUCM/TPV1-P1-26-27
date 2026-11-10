#pragma once
#include "MobileObject.h"

constexpr int ARROW_SIZE = 20;

class Arrow : public MobileObject
{
public:
	Arrow(Game* game, Vector2D<float> pos, Texture* text, float speed);

	void render() const override;
	bool update(float delta) override ;

private:
	Rectangle _colRec;
};

