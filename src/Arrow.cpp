#include "Arrow.h"

Arrow::Arrow(Game* game, Vector2D<float> pos, Texture* text, float speed) 
: _game(game), _text(text) {
	_renderRec = Rectangle(pos, ARROW_SIZE * 5, ARROW_SIZE);
	_vel = Vector2D(speed / 10, 0.0f);

	_colRec = Rectangle(pos + Vector2D((float)ARROW_SIZE * 4, 0.0f), ARROW_SIZE, ARROW_SIZE);
}

Arrow::~Arrow() {

}

void Arrow::render() {
	if (_text != nullptr) {
		_text->renderFrame(_renderRec.to_sdl(), 0, 0);
	}

	_game->checkCollision(_colRec);
}

bool Arrow::update(float delta) {
	_renderRec.move(_vel);
	_colRec.move(_vel);

	if (_renderRec.getTopLeftCorner().getX() > Game::WINDOW_WIDTH) return false;
	else return true;
}

