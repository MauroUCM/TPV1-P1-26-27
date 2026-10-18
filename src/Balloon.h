#pragma once
#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"

class Balloon
{
public:
	Balloon(Vector2D<float> pos, float vel, Texture* text, int color = 0);
	~Balloon();

	void render();
	bool update(float delta);

	bool hit(const Rectangle& obj);

private:
	Vector2D<float> _pos;
	Vector2D<float> _vel;

	Rectangle _rec;
	Texture* _text;

	int _color;
	bool _alive = true;
};

