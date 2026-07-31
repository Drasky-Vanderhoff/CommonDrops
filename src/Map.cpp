#include "Map.h"

using namespace sf;

Map::Map(
    const Texture& backgroundTexture,
    const Texture& tileMapTexture,
    const Vector2i& tileMapFrameSize,
    const TilesPositionsType& positions
)
    : map(nullptr),
      texture(backgroundTexture.getSize())
{
    const Renderable background(backgroundTexture);

    texture.clear(Color::White);
    texture.draw(background.getSprite());

    TilesType tiles;

    const Vector2i tilesDimensions(
        static_cast<int>(tileMapTexture.getSize().x) / tileMapFrameSize.x,
        static_cast<int>(tileMapTexture.getSize().y) / tileMapFrameSize.y
    );

    for (int x = 0; x < tilesDimensions.x; ++x)
    {
        for (int y = 0; y < tilesDimensions.y; ++y)
        {
            tiles.emplace_back(
                tileMapTexture,
                tileMapFrameSize,
                Vector2i(
                    tileMapFrameSize.x * x,
                    tileMapFrameSize.y * y
                )
            );
        }
    }

    for (const auto& position : positions)
    {
        renderTileInPosition(
            tiles[position.z].getSprite(),
            Vector2f(
                static_cast<float>(position.x * tileMapFrameSize.x),
                static_cast<float>(position.y * tileMapFrameSize.y)
            )
        );
    }

    texture.display();
    map = new Renderable(texture.getTexture());
}

void Map::renderTileInPosition(
    Sprite sprite,
    const Vector2f position
)
{
    sprite.setPosition(position);
    texture.draw(sprite);
}

void Map::render(RenderWindow* window)
{
    window->draw(map->getSprite());
}

Map::~Map()
{
    delete map;
}
