#include "Bow.h"
#include "game.h"

Bow::Bow(Vector2D<float> pos, float speed, Texture* text, int arrows)
	: _pos(pos), _speed(speed / 10), _text(text), _arrows(arrows) {
	_rec = Rectangle(pos, BOW_SIZE, BOW_SIZE);
	_armed = false;
	_vel = Vector2D<float>(0.0f, 0.0f);
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
	_rec.move(_vel * delta);

	//std::cout << _rec.getTopLeftCorner() << "\n";

	//if (_rec.getTopLeftCorner().getY() > Game::WINDOW_HEIGHT - _rec.getHeight()) {
	//	_rec.getTopLeftCorner().setY((float)Game::WINDOW_HEIGHT - _rec.getHeight() - 1);
	//}
	//else if (_rec.getTopLeftCorner().getY() < 0) {
	//	_rec.getTopLeftCorner().setY(1.0f);
	//}
}

void Bow::handleEvent(const SDL_Event& event) {

	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key)
		{
		case SDLK_DOWN:
			if (_rec.getTopLeftCorner().getY() < Game::WINDOW_HEIGHT - _rec.getHeight()) _vel.setY(_speed);
			break;
		case SDLK_UP:
			if (_rec.getTopLeftCorner().getY() > 0) _vel.setY(-_speed);
			break;
		case SDLK_LEFT:
			if(_arrows > 0) _armed = true;
			break;
		case SDLK_RIGHT:
			shoot();
			break;
		default:
			break;
		}
	}if (event.type == SDL_EVENT_KEY_UP) {
		switch (event.key.key)
		{
		case SDLK_DOWN:
			_vel.setY(0.0f);
			break;
		case SDLK_UP:
			_vel.setY(0.0f);
			break;
		default:
			break;
		}
	}
}

void Bow::shoot() {
	if (_armed) {
		_armed = false;
		_arrows--;
	}
}
