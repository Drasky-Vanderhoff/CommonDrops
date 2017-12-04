#pragma once
#include "Animatable.h"

enum CrystalColor{BLUE, GREEN, GREY, ORANGE, PINK, YELLOW, _CRYSTAL_COLOR_SIZE};

static sf::Texture blueCrystalColorTexture;
static sf::Texture greenCrystalColorTexture;
static sf::Texture greyCrystalColorTexture;
static sf::Texture orangeCrystalColorTexture;
static sf::Texture pinkCrystalColorTexture;
static sf::Texture yellowCrystalColorTexture;

class Crystal :
	public Animatable
{
private:
	const CrystalColor color;
public:
	Crystal::Crystal(const CrystalColor color);
	static void Crystal::initializeClass();
	CrystalColor getColor() const;
	~Crystal();
};

