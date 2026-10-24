#pragma once
#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"

constexpr int BALLOON_SIZE = 150;

class Balloon
{
public:
	Balloon(Vector2D<float> pos, float vel, Texture* text, int color = 0);

	void render() const;
	bool update(float delta);

	bool hit(const Rectangle& obj);

private:
	Vector2D<float> _pos;
	Vector2D<float> _vel;

	Rectangle _rec;
	Texture* _text;

	int _color;
	int _animationState;
	bool _alive = true;
};

