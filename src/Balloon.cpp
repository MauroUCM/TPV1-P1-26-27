#include "Balloon.h"

Balloon::Balloon(Vector2D<float> pos, Vector2D<float> vel, Texture* text, int color) : 
	_pos(pos), _vel(vel), _text(text) {
	_rec = Rectangle(pos, 10, 10);

}

Balloon::~Balloon() {

}

void Balloon::render() {
	if (_text != nullptr) {
		_text->renderFrame(_rec.to_sdl(), 1, 1);
	}
}

bool Balloon::update(float delta) {
	_rec.move(_vel);

	return _alive;
}

bool Balloon::hit(const Rectangle& obj) {
	return _rec.hasIntersection(obj);
}
