#include "Balloon.h"

Balloon::Balloon(Game* gm, Vector2D<float> pos, float vel, Texture* text, int color)
	: MobileObject(gm, text, new Rectangle(pos, BALLOON_SIZE), Vector2D(0.0f, 1.0f)* (vel* Game::SPEED_RATIO)), 
	_color(color) {
	_animationState = 0;
}

void Balloon::render() const {
	if (_text != nullptr) {
		_text->renderFrame(_rec->to_sdl(), _color, _animationState);
	}
}

bool Balloon::update(float delta) {
	MobileObject::update(delta);

	if (_rec->getTopLeftCorner().getY() < -BALLOON_SIZE) _alive = false;

	if (!_alive) _animationState++;
	return _animationState <= 6;
}

// verifica si hay impacto
bool Balloon::hit(const Rectangle& obj) {
	if (_rec->hasIntersection(obj) && _alive) {
		_alive = false;
		return true;
	}
	else return false;
}
