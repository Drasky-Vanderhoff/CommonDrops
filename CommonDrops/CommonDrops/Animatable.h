#pragma once
#include "Renderable.h"
class Animatable :
	public Renderable
{
private:
	const unsigned int frames;
	unsigned int currentFrame;
	sf::Time lastTime;
public:
	Animatable(const sf::Texture &texture, const sf::Vector2u frameSize, const unsigned int frames);
	static void Animatable::initializeClass(sf::Clock *clock);
	sf::Sprite getNextFrame(const float vel);
	sf::Sprite getNextFrame(const float vel, const unsigned int row);
	~Animatable();
};

