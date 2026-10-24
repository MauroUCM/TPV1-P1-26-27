#pragma once
#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"
#include "game.h"

constexpr int BOW_SIZE = 100;

class Bow
{
public:
	Bow(Game* game, Vector2D<float> pos, float speed, Texture* text);
	~Bow();

	void render() const;
	bool update(float delta);
	void handleEvent(const SDL_Event& event);

private:
	void shoot();

	Game* _game;

	Vector2D<float> _pos;
	Vector2D<float> _vel;
	float _speed;

	Rectangle _rec;
	Texture* _text;

	bool _armed;
};

