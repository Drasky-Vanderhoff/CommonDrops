#pragma once
#include "Renderable.h"

typedef std::vector<Renderable> TilesType;

typedef std::vector<sf::Vector3i> TilesPositionsType;
class Map
{
private:
	Renderable* map;
	sf::RenderTexture texture;
	void Map::renderTileinPosition(sf::Sprite& sprite, const sf::Vector2f position);
public:
	Map::Map(const sf::Texture& backgroundTexture, const sf::Texture& tileMapTexture,
			 const sf::Vector2i& tileMapFrameSize, TilesPositionsType& positions);
	void render(sf::RenderWindow* window);
	~Map();
};

