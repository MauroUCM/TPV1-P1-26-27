#include "Butterfly.h"
#include <cmath>
#include <numbers>

Butterfly::Butterfly(Game* game, Texture* text, Vector2D<float> pos)
	: MobileObject(game, text, new Rectangle(pos, BTF_SIZE)) {
	_speed = _gm->generateRndInt(BTF_MIN_SPEED, BTF_MAX_SPEED) * Game::SPEED_RATIO;
	changeDirRnd();
}

void Butterfly::render() const {
	if (_text != nullptr) {
		_text->renderFrame(_rec->to_sdl(), _animState, _animFrame);
	}
}

bool Butterfly::update(float delta) {
	MobileObject::update(delta);
	_timeSncLastFrame += delta;

	if (_alive) {
		// gestión de limites
		manageLimits();

		_timeSncLastDirChng += delta;
		if (_timeSncLastDirChng >= _nextDirChange) changeDirRnd();

		// animacion
		if (_timeSncLastFrame >= Game::ANIM_FRAMES_RATE) {
			_animFrame++;
			_timeSncLastFrame = 0;
			if (_animFrame >= _text->getNumColumns()) {
				if (_animState == TURNING_LEFT) _animState = MOVING_LEFT;
				else if (_animState == TURNING_RIGHT) _animState = MOVING_RIGHT;
				_animFrame = 0;
			}
		}

		return true;
	}
	else return _rec->getTopLeftCorner().getY() < Game::WINDOW_HEIGHT;
}

void Butterfly::changeDirRnd() {
	float ang = _gm->generateRndInt(0, 360) * (std::numbers::pi / 180);
	float oldX = _vel.getX();

	_vel = { std::cos(ang), std::sin(ang) };
	_vel = _vel * _speed;

	if ((_vel.getX() >= 0.0f) != (oldX >= 0.0f)) {
		if (_vel.getX() >= 0.0f) _animState = TURNING_RIGHT;
		else _animState = TURNING_LEFT;
		_animFrame = 0;
	}

	_nextDirChange = _gm->generateRndInt(BTF_MIN_TURN_TIME, BTF_MAX_TURN_TIME);
	_timeSncLastDirChng = 0;
}

bool Butterfly::hit(const Rectangle& obj) {
	if (_rec->hasIntersection(obj) && _alive) {
		_alive = false;
		_gm->addScore(BTF_PENALTY, 1);
		_gm->substractBtf();
		_vel = { 0.0f, FALL_SPEED * Game::SPEED_RATIO };
	}
	return false;
}

void Butterfly::manageLimits() {
	if (_vel.getX() >= 0) {	// en el eje X
		if (_rec->getTopLeftCorner().getX() + BTF_SIZE >= Game::WINDOW_WIDTH) {
			_vel.setX(-_vel.getX());
			_animState = TURNING_LEFT;
			_animFrame = 0;
		}
	}
	else {
		if (_rec->getTopLeftCorner().getX() <= 0) {
			_vel.setX(-_vel.getX());
			_animState = TURNING_RIGHT;
			_animFrame = 0;
		}
	}
	if (_vel.getY() >= 0) {	// en el eje Y
		if (_rec->getTopLeftCorner().getY() + BTF_SIZE >= Game::WINDOW_HEIGHT) _vel.setY(-_vel.getY());
	}
	else {
		if (_rec->getTopLeftCorner().getY() <= 0) _vel.setY(-_vel.getY());
	}
}
