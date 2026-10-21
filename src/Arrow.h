#pragma once
#include "game.h"
#include "rectangle.h"
#include "texture.h"

constexpr int ARROW_SIZE = 20;

class Arrow
{
public:
	Arrow(Game* game, Vector2D<float> pos, Texture* text, float speed);
	~Arrow();

	void render();
	bool update(float delta);

private:
	Vector2D<float> _vel;

	Rectangle _renderRec;
	Rectangle _colRec;
	Texture* _text;
	
	Game* _game;
};

