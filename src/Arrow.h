#pragma once
#include "MobileObject.h"

constexpr int ARROW_SIZE = 20;

class Arrow : public MobileObject
{
public:
	Arrow(Game* gm);
	Arrow(Game* game, Vector2D<float> pos, float speed);
	~Arrow();

	void render() const override;
	bool update(float delta) override;

	virtual void save(std::ostream& out) override;
	virtual void load(std::istream& in) override;

private:
	Rectangle _colRec;

	int scoreMult = 1;
};

