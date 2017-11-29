#include "stdafx.h"
#include "Crystal.h"

using namespace sf;

Texture* getTexture(CrystalColor color)
{
	switch (color)
	{
	case BLUE:
		return &blueCrystalColorTexture;
		break;
	case GREEN:
		return &greenCrystalColorTexture;
		break;
	case GREY:
		return &greyCrystalColorTexture;
		break;
	case ORANGE:
		return &orangeCrystalColorTexture;
		break;
	case PINK:
		return &pinkCrystalColorTexture;
		break;
	case YELLOW:
		return &yellowCrystalColorTexture;
		break;
	default:
		throw "Not a valid color for a Crystal";
		break;
	}
}

Crystal::Crystal(const CrystalColor color)
	   : Animatable(*getTexture(color), Vector2u(32, 32), 8), color(color)
{
}

void Crystal::initializeClass() {
	blueCrystalColorTexture.loadFromFile("graphics/crystals-32/blue.png");
	greenCrystalColorTexture.loadFromFile("graphics/crystals-32/green.png");
	greyCrystalColorTexture.loadFromFile("graphics/crystals-32/grey.png");
	orangeCrystalColorTexture.loadFromFile("graphics/crystals-32/orange.png");
	pinkCrystalColorTexture.loadFromFile("graphics/crystals-32/pink.png");
	yellowCrystalColorTexture.loadFromFile("graphics/crystals-32/yellow.png");
};


Crystal::~Crystal()
{
}
