#pragma once
#include "game.h"
#include "rectangle.h"

constexpr int ARROW_SIZE = 50;

class Arrow
{
public:
	Arrow(Game& game, Vector2D<float> pos, float speed);
	~Arrow();

	void render();
	bool update(float delta);

private:
	Rectangle _rec;
	Vector2D<float> _vel;
	
	Game& _game;
};

