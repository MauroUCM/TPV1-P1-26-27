#pragma once
#include "SceneObject.h"

constexpr float ICON_SIZE = 10.0f;

class InfoBar : public SceneObject
{
public:
	InfoBar(Game* game, Texture* text);

	void render() const override;
	bool update(float delta) override { return true; };

private:
	const Vector2D<float> _sepDist = { ICON_SIZE * 2, 0.0f };
};

