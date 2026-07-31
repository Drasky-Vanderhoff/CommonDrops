#pragma once
#include "Renderable.h"

typedef std::vector<Renderable> TilesType;

typedef std::vector<sf::Vector3i> TilesPositionsType;
class Map
{
private:
	Renderable* map;
	sf::RenderTexture texture;
	void renderTileinPosition(sf::Sprite sprite, sf::Vector2f position);
public:
	Map(const sf::Texture& backgroundTexture, const sf::Texture& tileMapTexture,
			 const sf::Vector2i& tileMapFrameSize, const TilesPositionsType& positions);
	void render(sf::RenderWindow* window);
	~Map();
};

