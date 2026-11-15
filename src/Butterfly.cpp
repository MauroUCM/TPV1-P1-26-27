#include "Butterfly.h"

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

		// animacion
		if (_timeSncLastFrame >= Game::ANIM_FRAMES_RATE) {
			_animFrame++;
			_timeSncLastFrame = 0;
			if (_animFrame >= _text->getNumColumns()) _animFrame = 0;
		}
	}



	return _rec->getTopLeftCorner().getY() < Game::WINDOW_HEIGHT;
}

void Butterfly::changeDirRnd() {
	//_vel = { _gm->generateRndInt(0, 100) / 100.0f, _gm->generateRndInt(0, 100) / 100.0f };
}

bool Butterfly::hit(const Rectangle& obj) {
	if (_rec->hasIntersection(obj) && _alive) {
		_alive = false;
		return true;
	}
	else return false;
}
