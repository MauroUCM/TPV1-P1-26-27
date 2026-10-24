#include "Balloon.h"

Balloon::Balloon(Vector2D<float> pos, float vel, Texture* text, int color) 
	: _pos(pos), _text(text), _color(color) {
	_vel = Vector2D(0.0f, 1.0f) * (vel / 10);
	_rec = Rectangle(pos, BALLOON_SIZE);
	_animationState = 0;
}

void Balloon::render() const {
	if (_text != nullptr) {
		_text->renderFrame(_rec.to_sdl(), _color, _animationState);
	}
}

bool Balloon::update(float delta) {
	_rec.move(_vel * delta);

	if (_rec.getTopLeftCorner().getY() < -BALLOON_SIZE) _alive = false;

	if (!_alive) _animationState++;
	return _animationState <= 6;
}

// verifica si hay impacto
bool Balloon::hit(const Rectangle& obj) {
	if (_rec.hasIntersection(obj) && _alive) {
		_alive = false;
		return true;
	}
	else return false;
}
