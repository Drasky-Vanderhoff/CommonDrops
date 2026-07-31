#pragma once

#include "Renderable.h"

#include <vector>

using TilesType = std::vector<Renderable>;
using TilesPositionsType = std::vector<sf::Vector3i>;

class Map
{
private:
    Renderable* map;
    sf::RenderTexture texture;

    void renderTileInPosition(
        sf::Sprite sprite,
        sf::Vector2f position
    );

public:
    Map(
        const sf::Texture& backgroundTexture,
        const sf::Texture& tileMapTexture,
        const sf::Vector2i& tileMapFrameSize,
        const TilesPositionsType& positions
    );

    void render(sf::RenderWindow* window);

    ~Map();
};
