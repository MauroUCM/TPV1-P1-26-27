#include "MobileObject.h"

MobileObject::MobileObject(Game* gm, Texture* text, Rectangle* rec, Vector2D<float> vel)
: SceneObject(gm, text, rec), _vel(vel) {

}

bool MobileObject::update(float delta) {
	_rec->move(_vel * delta);

	return true;
}
