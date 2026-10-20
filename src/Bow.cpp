#include "Bow.h"
#include "game.h"

Bow::Bow(Vector2D<float> pos, float vel, Texture* text, int arrows)
	: _pos(pos),_vel(vel), _text(text), _arrows(arrows) {
	_rec = Rectangle(pos, BOW_SIZE, BOW_SIZE);
	_armed = false;
}

Bow::~Bow() {

}

void Bow::render() const {
	if (_text != nullptr) {
		if(_armed) _text->renderFrame(_rec.to_sdl(), 0, 0);
		else _text->renderFrame(_rec.to_sdl(), 0, 1);
	}
}

void Bow::update(float delta) {

}

void Bow::handleEvent(const SDL_Event& event) {
	switch (event.key.key)
	{
	case SDLK_DOWN:
		if (_rec.getTopLeftCorner().getY() < Game::WINDOW_HEIGHT - _rec.getHeight()) _rec.move({ 0.0f, _vel });
		break;
	case SDLK_UP:
		if(_rec.getTopLeftCorner().getY() > 0) _rec.move({ 0.0f, -_vel });
		break;
	case SDLK_LEFT:
		_armed = true;
		break;
	case SDLK_RIGHT:
		shoot();
		break;
	default:
		break;
	}
}

void Bow::shoot() {
	if (_armed) {
		_armed = false;
		_arrows--;
	}
}
