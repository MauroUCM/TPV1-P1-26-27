#include "Bow.h"
#include "game.h"

Bow::Bow(Game* game, Vector2D<float> pos, float speed, Texture* text)
	: _game(game), _speed(speed * Game::SPEED_RATIO), _text(text) {
	_rec = Rectangle(pos, BOW_SIZE);
	_armed = false;
	_vel = Vector2D<float>(0.0f, 0.0f);
}

void Bow::render() const {
	if (_text != nullptr) {
		if(_armed) _text->renderFrame(_rec.to_sdl(), 0, 0);
		else _text->renderFrame(_rec.to_sdl(), 0, 1);
	}
}

bool Bow::update(float delta) {
	if (_rec.getTopLeftCorner().getY() < 0) {
		_vel = Vector2D<float>(0.0f, 0.0f);
		_rec.moveToY(0.0f);
	}
	else if (_rec.getTopLeftCorner().getY() > Game::WINDOW_HEIGHT - BOW_SIZE) {
		_vel = Vector2D<float>(0.0f, 0.0f);
		_rec.moveToY(Game::WINDOW_HEIGHT - BOW_SIZE);
	}

	_rec.move(_vel * delta);

	return true;
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
			if(_game->getArrows() > 0) _armed = true;
			break;
		case SDLK_RIGHT:
			shoot();
			break;
		default:
			break;
		}
	}if (event.type == SDL_EVENT_KEY_UP) {	// detiene el arco cuando no se pulsa nada
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
		_game->addArrow(_rec.getTopLeftCorner() + Vector2D(0.0f, (float)BOW_SIZE / 2));
	}
}
