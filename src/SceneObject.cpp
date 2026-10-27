#include "SceneObject.h"

SceneObject::SceneObject(Game* gm, Texture* text, Rectangle* rec) 
	: GameObject(gm), _rec(rec), _text(text) {

}

SceneObject::~SceneObject() {
	delete _rec;
}

bool SceneObject::hit(const Rectangle& rec) {
	if (_rec->hasIntersection(rec)) {
		return true;
	}
	else return false;
}
