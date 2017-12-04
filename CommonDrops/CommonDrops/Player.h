#pragma once
#include "Animatable.h"
#include "CrystalMatrix.h"
#include "Crystal.h"

enum CharacterState { RIGHT, LEFT, ACTION };

class Player
{
private:
	sf::Texture textureCharacter;
	Animatable * character;
	CrystalMatrix * objective;
	CrystalMatrix stack;
	CrystalColor currentColor = CrystalColor::_CRYSTAL_COLOR_SIZE;
	CharacterState characterActionState = CharacterState::RIGHT;
	const sf::Vector2u characterInitialPosition;
	const sf::Vector2u characterSpriteSize;
	unsigned int playerPosition = 0;
	const unsigned int playerLimitPosition;
public:
	/* TODO: There are some elements 
	   ( crystalQueueSize, characterInitialPosition, 
	     playerLimitPosition, crystalQueueSize )
	   that can be derived from objective since they need
	   a space cooherence.
	*/
	Player(const char *characterTextureFile,
		   const sf::Vector2u characterInitialPosition, 
		   const unsigned int playerLimitPosition,
		   const sf::Vector2u crystalQueuePosition,
		   const unsigned int crystalQueueSize, 
		   CrystalMatrix * objective);
	bool processEvents(bool *gameOver, unsigned int* score);
	void drawPlayer(sf::RenderWindow &window);
	~Player();
};


