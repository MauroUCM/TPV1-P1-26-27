#pragma once
#include"GameObject.h"
#include "texture.h"
#include "rectangle.h"

class SceneObject : public GameObject
{
public:
	SceneObject(Game* gm, Texture* text, Rectangle* rec);
	~SceneObject();

	virtual void render() const override = 0;
	virtual bool update(float delta) override = 0;

	// de normal devuelve false, cada objeto debe configurarlo en su clase
	virtual bool hit(const Rectangle&);

protected:
	Rectangle* _rec;
	Texture* _text;
};
