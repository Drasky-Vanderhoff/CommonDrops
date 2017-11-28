#include "stdafx.h"
#include "Animatable.h"

using namespace sf;

static Clock *_Animatable_clock = nullptr;
static RenderWindow *_Renderable_window;


void Animatable::initializeClass(Clock *clock) {
	_Animatable_clock = clock;
};

Animatable::Animatable(const Texture &texture, 
					   const Vector2u frameSize, const unsigned int frames)
		  : Renderable(texture, frameSize),
			frames(frames - 1), currentFrame(0), 
			lastTime(_Animatable_clock->getElapsedTime())
{
}

Sprite Animatable::getNextFrame(const float vel)
{
	if (lastTime.asSeconds() + vel < _Animatable_clock->getElapsedTime().asSeconds()) {
		(currentFrame >= frames) ? currentFrame = 0 : currentFrame++;
		lastTime = _Animatable_clock->getElapsedTime();
	}
	return getSprite(currentFrame, 0);
}

Animatable::~Animatable()
{
}
