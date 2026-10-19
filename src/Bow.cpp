#include "Bow.h"

Bow::Bow(Vector2D<float> pos, float vel, Texture* text, int flechas) 
	: _pos(pos), _text(text), _flechas(flechas) {
	_vel = Vector2D<float>(0.0f, 1.0f) * vel;

}

Bow::~Bow() {

}

void Bow::render() const {

}

void Bow::update(float delta) {

}

void Bow::handleEvent(const SDL_Event& event) {

}
