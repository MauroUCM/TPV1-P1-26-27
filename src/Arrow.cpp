#include "Arrow.h"

Arrow::Arrow(Game& game, Vector2D<float> pos, float speed) 
: _game(game) {
	_rec = Rectangle(pos, ARROW_SIZE);
	_vel = Vector2D(speed, 0.0f);
}

Arrow::~Arrow() {

}

void Arrow::render() {

}

bool Arrow::update(float delta) {
	_rec.move(_vel);

	return true;
}

