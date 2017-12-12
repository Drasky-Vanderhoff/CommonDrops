#include "stdafx.h"
#include "Renderable.h"

using namespace sf;

static RenderWindow *_Renderable_window;

void Renderable::initializeClass(RenderWindow *window) {
	_Renderable_window = window;
};

Renderable::Renderable(const Texture &texture) 
		  : Renderable(texture, texture.getSize())
{}

Renderable::Renderable(const Texture &texture, const Vector2u frameSize)
		  : texture(texture), frameSize(frameSize), sprite(new Sprite)
{
	sprite->setTexture(texture);
	sprite->setTextureRect(IntRect(0, 0, frameSize.x, frameSize.y));
}

Renderable::Renderable(const Texture &texture, const Vector2i frameSize, const Vector2i framePosition)
	: texture(texture), frameSize(frameSize), sprite(new Sprite)
{
	sprite->setTexture(texture);
	sprite->setTextureRect(IntRect(framePosition, frameSize));
}

// FIX: Deleting the sprite generates problems
Renderable::~Renderable()
{
//	delete sprite;
}

Sprite Renderable::getSprite() {
	return *sprite;
}

Sprite Renderable::getSprite(const unsigned int frameIdxX, const unsigned int frameIdxY) {
	sprite->setTextureRect(IntRect (frameIdxX * frameSize.x, frameIdxY * frameSize.y, frameSize.x, frameSize.y));
	return *sprite;
}

void Renderable::move(const float x, const float y) {
	sprite->setPosition(x, y);
}

void Renderable::scale(const float x, const float y) {
	sprite->setScale(x, y);
}
