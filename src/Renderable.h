#pragma once

#include <SFML/Graphics.hpp>

class Renderable
{
private:
    sf::Sprite sprite;
    sf::Vector2i frameSize;

public:
    explicit Renderable(const sf::Texture& texture);

    Renderable(
        const sf::Texture& texture,
        sf::Vector2u frameSize
    );

    Renderable(
        const sf::Texture& texture,
        sf::Vector2i frameSize,
        sf::Vector2i framePosition
    );

    sf::Sprite getSprite() const;

    sf::Sprite getSprite(
        unsigned int frameIdxX,
        unsigned int frameIdxY
    );

    void move(float x, float y);
    void scale(float x, float y);
};
