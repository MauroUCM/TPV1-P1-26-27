#pragma once
#include "game.h"
#include "rectangle.h"
#include "texture.h"

constexpr float ICON_SIZE = 10.0f;

class InfoBar
{
public:
	InfoBar(Game* game, Texture* text);

	void render() const;

private:
	Game* _game;
	Texture* _text;
	Rectangle _rec;

	const Vector2D<float> _sepDist = { ICON_SIZE * 2, 0.0f };
};

