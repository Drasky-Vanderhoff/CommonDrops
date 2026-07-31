#include "Renderable.h"

using namespace sf;

Renderable::Renderable(const Texture& texture)
    : Renderable(texture, texture.getSize())
{
}

Renderable::Renderable(
    const Texture& texture,
    const Vector2u frameSize
)
    : sprite(
          texture,
          IntRect(
              {0, 0},
              {
                  static_cast<int>(frameSize.x),
                  static_cast<int>(frameSize.y)
              }
          )
      ),
      frameSize(
          static_cast<int>(frameSize.x),
          static_cast<int>(frameSize.y)
      )
{
}

Renderable::Renderable(
    const Texture& texture,
    const Vector2i frameSize,
    const Vector2i framePosition
)
    : sprite(texture, IntRect(framePosition, frameSize)),
      frameSize(frameSize)
{
}

Sprite Renderable::getSprite() const
{
    return sprite;
}

Sprite Renderable::getSprite(
    const unsigned int frameIdxX,
    const unsigned int frameIdxY
)
{
    sprite.setTextureRect(
        IntRect(
            {
                static_cast<int>(frameIdxX) * frameSize.x,
                static_cast<int>(frameIdxY) * frameSize.y
            },
            frameSize
        )
    );

    return sprite;
}

void Renderable::move(const float x, const float y)
{
    sprite.setPosition({x, y});
}

void Renderable::scale(const float x, const float y)
{
    sprite.setScale({x, y});
}
