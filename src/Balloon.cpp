#include "Balloon.h"

Balloon::Balloon(Vector2D<float> pos, float vel, Texture* text, int color) 
	: _pos(pos), _text(text), _color(color) {
	_vel = Vector2D(0.0f, 1.0f) * (vel / 1000);
	_rec = Rectangle(pos, 150, 150);
}

Balloon::~Balloon() {

}

void Balloon::render() {
	if (_text != nullptr) {
		_text->renderFrame(_rec.to_sdl(), _color, 0);
	}
}

bool Balloon::update(float delta) {
	_rec.move(_vel * delta);

	return _alive;
}

bool Balloon::hit(const Rectangle& obj) {
	return _rec.hasIntersection(obj);
}
