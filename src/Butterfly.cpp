#include "Butterfly.h"

Butterfly::Butterfly(Game* game, Texture* text) : MobileObject(game, text, new Rectangle({ 0.0f, 0.0f }, BUTTERFLY_SIZE)) {
	changeSpeedRnd();
}

void Butterfly::render() const {

}

bool Butterfly::update(float delta) {
	MobileObject::update(delta);

}

void Butterfly::changeSpeedRnd() {

}
