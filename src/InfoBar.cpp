#include "InfoBar.h"

InfoBar::InfoBar(Game* game, Texture* text)
	: SceneObject(game, text, new Rectangle(Vector2D(0.0f, ICON_SIZE * 2), ICON_SIZE * 5, ICON_SIZE)) {

}

void InfoBar::render() const {
	int arrows = _gm->getArrows();

	// el renderizado se repite cuantas veces flechas haya en game 
	for (int i = 0; i < arrows; i++) {
		_text->render(_rec->moved(_sepDist * (float)i).to_sdl(), -90);
	}
}
