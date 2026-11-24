#include "Arrow.h"

Arrow::Arrow(Game* gm) : MobileObject(gm, gm->getTexture(Game::ARROW)) {

}

Arrow::Arrow(Game* game, Vector2D<float> pos, float speed) 
: MobileObject(game, game->getTexture(Game::ARROW), new Rectangle(pos, ARROW_SIZE * 5, ARROW_SIZE), 
	Vector2D(speed* Game::SPEED_RATIO, 0.0f)) {
	_colRec = Rectangle(pos + Vector2D((float)ARROW_SIZE * 4, 0.0f), ARROW_SIZE / 5, ARROW_SIZE / 3);
	_gm->addUnclosable(1);
}

Arrow::~Arrow() {
	_gm->addUnclosable(-1);
}

void Arrow::render() const {
	if (_text != nullptr) {
		_text->renderFrame(_rec->to_sdl(), 0, 0);
	}
}

bool Arrow::update(float delta) {
	MobileObject::update(delta);

	_colRec.move(_vel * delta);
	if (_gm->checkCollision(_colRec)) {
		_gm->addScore(_gm->getBalPoints(), scoreMult);
		scoreMult++;
	}

	// comprobacion de si sale de la escenea
	if (_rec->getTopLeftCorner().getX() > Game::WINDOW_WIDTH) return false;
	else return true;
}

void Arrow::save(std::ostream& out) {
	out << "A ";
	MobileObject::save(out);
	out << scoreMult << "\n";
}

void Arrow::load(std::istream& in) {
	MobileObject::load(in);
	in >> scoreMult;
}
