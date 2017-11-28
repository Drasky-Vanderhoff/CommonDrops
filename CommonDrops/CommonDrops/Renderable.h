#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Renderable
{
private:
	sf::Sprite *sprite;
	const sf::Texture &texture;
	const sf::Vector2u frameSize;
public:
	static void initializeClass(sf::RenderWindow *window);
	Renderable(const sf::Texture &texture);
	Renderable(const sf::Texture &texture, const sf::Vector2u frameSize);
	sf::Sprite getSprite();
	sf::Sprite getSprite(const unsigned int frameIdxX, const unsigned int frameIdxY);
	void move(const float x, const float y);
	~Renderable();
};

