#include "Arrow.h"

Arrow::Arrow(Game* game, Vector2D<float> pos, Texture* text, float speed) 
: _game(game), _text(text) {
	_rec = Rectangle(pos, ARROW_SIZE * 5, ARROW_SIZE);
	_vel = Vector2D(speed / 10, 0.0f);
}

Arrow::~Arrow() {

}

void Arrow::render() {
	if (_text != nullptr) {
		_text->renderFrame(_rec.to_sdl(), 0, 0);
	}
}

bool Arrow::update(float delta) {
	_rec.move(_vel);

	if (_rec.getTopLeftCorner().getX() > Game::WINDOW_WIDTH) return false;
	else return true;
}

