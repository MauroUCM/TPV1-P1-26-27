#include "Bow.h"

Bow::Bow(Vector2D<float> pos, float vel, Texture* text, int arrows)
	: _pos(pos),_vel(vel), _text(text), _arrows(arrows) {
	_rec = Rectangle(pos, BOW_SIZE, BOW_SIZE);
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

}
