#include "SceneObject.h"

SceneObject::SceneObject(Game* gm, Texture* text, Rectangle* rec) 
	: GameObject(gm), _rec(rec), _text(text) {

}

SceneObject::~SceneObject() {
	delete _rec;
}

bool SceneObject::hit(const Rectangle& rec) {
	return false;
}

void SceneObject::save(std::ostream& out) {
	out << _rec->getTopLeftCorner() << " " << _rec->getWidth() 
		<< " " << _rec->getHeight() << " ";
}

void SceneObject::load(std::istream& in) {

}
