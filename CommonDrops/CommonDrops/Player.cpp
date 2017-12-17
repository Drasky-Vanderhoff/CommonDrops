#include "stdafx.h"
#include "Player.h"
#include "CrystalMatrix.h"

using namespace sf;

Player::Player(const char *characterTextureFile,
			   const sf::Vector2u characterInitialPosition, 
			   const unsigned int playerLimitPosition,
			   const sf::Vector2u crystalQueuePosition,
			   const unsigned int crystalQueueSize, CrystalMatrix * sourceMatrix):
			   stack(crystalQueuePosition, Vector2u(1, crystalQueueSize)),
			   playerLimitPosition(playerLimitPosition),
			   characterInitialPosition(characterInitialPosition),
			   objective(sourceMatrix)
{
	textureCharacter.loadFromFile(characterTextureFile);
	character = new Animatable(textureCharacter, Vector2u(14, 14), 3);
	character->scale(2.0f, 2.0f);
	character->move(characterInitialPosition.x, characterInitialPosition.y);
}

bool Player::processEvents(bool *gameOver, unsigned int* score)
{
	bool result = true;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (playerPosition > 0) playerPosition--;
		character->move(characterInitialPosition.x + playerPosition * 32, characterInitialPosition.y);
		characterActionState = CharacterState::LEFT;
		result = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (playerPosition < playerLimitPosition) playerPosition++;
		character->move(characterInitialPosition.x + playerPosition * 32, characterInitialPosition.y);
		characterActionState = CharacterState::RIGHT;
		result = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::X) && 
		(currentColor == CrystalColor::_CRYSTAL_COLOR_SIZE ||
		 currentColor == objective->getBackCrystalColor(playerPosition)))
	{
		if (currentColor == CrystalColor::_CRYSTAL_COLOR_SIZE) currentColor = objective->getBackCrystalColor(playerPosition);
		if (currentColor == CrystalColor::_CRYSTAL_COLOR_SIZE) return false; // We try to took crystals from a empty row when we have none.
		while (objective->getBackCrystalColor(playerPosition) == currentColor) stack.trasferCrystalFromMatrix(0, objective, playerPosition);
		characterActionState = CharacterState::ACTION;
		result = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::C))
	{
		if (stack.getBackCrystalColor(0) != CrystalColor::_CRYSTAL_COLOR_SIZE && !*gameOver) {
			while (stack.getBackCrystalColor(0) != CrystalColor::_CRYSTAL_COLOR_SIZE && !*gameOver)
			{
				*gameOver = objective->trasferCrystalFromMatrix(playerPosition, &stack, 0);
			}

			*score += objective->destroyRepeatedCrystalsFromColumn(playerPosition, currentColor);
			characterActionState = CharacterState::ACTION;
			currentColor = CrystalColor::_CRYSTAL_COLOR_SIZE;
			result = false;
		}
	}

	return result;
}

void Player::drawPlayer(sf::RenderWindow &window)
{
	window.draw(character->getNextFrame(.15, characterActionState));
	stack.drawMatrix(window);
}

Player::~Player()
{
	delete character;
}
