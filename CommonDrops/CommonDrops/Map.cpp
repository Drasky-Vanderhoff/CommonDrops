#include "stdafx.h"
#include "Map.h"

using namespace sf;

Map::Map(const Texture& backgroundTexture, const Texture& tileMapTexture,
	const Vector2i& tileMapFrameSize, TilesPositionsType& positions)
{
	Renderable background = Renderable(backgroundTexture);
	
	texture.create(backgroundTexture.getSize().x, backgroundTexture.getSize().y);
	texture.clear(Color::White);
	texture.draw(background.getSprite());

	TilesType tiles = TilesType();
	Vector2i tilesPositions(tileMapTexture.getSize().x / tileMapFrameSize.x, tileMapTexture.getSize().y / tileMapFrameSize.y);

	// Prepare tiles for loading of a specific map.
	for (size_t i = 0; i < tilesPositions.x; i++)
		for (size_t j = 0; j < tilesPositions.y; j++)
			tiles.push_back(Renderable(tileMapTexture, tileMapFrameSize, Vector2i(tileMapFrameSize.x * i, tileMapFrameSize.y * j)));

	// Render the tiles over the background.
	for (TilesPositionsType::iterator it = positions.begin(); it != positions.end(); ++it) 
		this->renderTileinPosition(tiles[it->z].getSprite(), Vector2f(it->x * tileMapFrameSize.x, it->y * tileMapFrameSize.y));

	map = new Renderable(texture.getTexture());
}

void Map::renderTileinPosition(Sprite& sprite, const Vector2f position)
{
	sprite.setPosition(position);
	texture.draw(sprite);
	texture.display();
}

void Map::render(RenderWindow* window)
{
	window->draw(map->getSprite());
}

Map::~Map()
{
	delete map;
}
