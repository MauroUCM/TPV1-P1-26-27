#pragma once
#include"GameObject.h"
#include "texture.h"
#include "rectangle.h"

class SceneObject : public GameObject
{
public:
	SceneObject(Game* gm, Texture* text, Rectangle* rec);
	virtual ~SceneObject();

	virtual void render() const override = 0;
	virtual bool update(float delta) override = 0;

	bool hit(const Rectangle&);

protected:
	Rectangle* _rec;
	Texture* _text;
};
