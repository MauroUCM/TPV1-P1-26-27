#include "Balloon.h"

Balloon::Balloon(Vector2D<float> pos, float vel, Texture* text, int color) 
	: _pos(pos), _text(text), _color(color) {
	_vel = Vector2D(0.0f, 1.0f) * (vel / 10);
	_rec = Rectangle(pos, BALLOON_SIZE);
}

Balloon::~Balloon() {

}

void Balloon::render() const {
	if (_text != nullptr) {
		_text->renderFrame(_rec.to_sdl(), _color, 0);
	}
}

bool Balloon::update(float delta) {
	_rec.move(_vel * delta);

	if (_rec.getTopLeftCorner().getY() < -BALLOON_SIZE) _alive = false;

	return _alive;
}

bool Balloon::hit(const Rectangle& obj) {
	if (_rec.hasIntersection(obj)) {
		_alive = false;
		return true;
	}
	else return false;
}
