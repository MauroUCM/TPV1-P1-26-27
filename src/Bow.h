#pragma once
#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"

class Bow
{
public:
	Bow(Vector2D<float> pos, float vel, Texture* text, int flechas);
	~Bow();

	void render() const;
	void update(float delta);
	void handleEvent(const SDL_Event& event);

private:
	Vector2D<float> _pos;
	Vector2D<float> _vel;

	Rectangle _rec;
	Texture* _text;

	bool _armed;
	int _flechas;
};

