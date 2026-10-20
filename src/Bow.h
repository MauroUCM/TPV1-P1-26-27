#pragma once
#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"

constexpr int BOW_SIZE = 100;

class Bow
{
public:
	Bow(Vector2D<float> pos, float vel, Texture* text, int arrows);
	~Bow();

	void render() const;
	void update(float delta);
	void handleEvent(const SDL_Event& event);

private:
	void shoot();

	Vector2D<float> _pos;
	float _vel;

	Rectangle _rec;
	Texture* _text;

	bool _armed;
	int _arrows;
};

