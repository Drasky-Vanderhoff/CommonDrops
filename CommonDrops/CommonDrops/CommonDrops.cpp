// HelloSFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "Renderable.h"
#include "Animatable.h"
#include "CrystalMatrix.h"

using namespace sf;

enum CharacterState { RIGHT, LEFT, ACTION };

const Vector2u windowsResolution(800, 600);
const Vector2u matrixDimensions(15, 10);
unsigned int playerCurrentPosition = 0;
const float playerWidth = 32.0f;
const unsigned int leftBorder = 100;
const unsigned int topBorder = 50;
const unsigned int bottomBorder = 500;
Crystal *newCristal;
CharacterState characterActionState = CharacterState::RIGHT;

int main()
{
	// Create a video mode object 
	VideoMode vm(windowsResolution.x, windowsResolution.y);

	// Create and open a window for the game 
	RenderWindow window(vm, "CommonDrops", Style::Resize);

	// Initializing Renderable class
	Renderable::initializeClass(&window);

	// Variable for update the scene
	Clock clock;
	bool isPaused = true;
	Animatable::initializeClass(&clock);

	// Make a background sprite
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/backgrounds/hills.png");
	Renderable background = Renderable(textureBackground);

	// Make a crystals matrix
	Crystal::initializeClass();
	CrystalMatrix matrix(Vector2u(leftBorder, topBorder), matrixDimensions);
	matrix.fillMatrixWithRandomCrystals();

	// Make player crystal holder
	CrystalMatrix crystalHolder(Vector2u(windowsResolution.x - 64, topBorder), Vector2u(1, matrixDimensions.y));
	Texture textureCharacter;
	textureCharacter.loadFromFile("graphics/character/green-bot.png");
	Animatable character = Animatable(textureCharacter, Vector2u(16, 16), 3);
	character.move(leftBorder, bottomBorder);
	character.scale(2.0f, 2.0f);
	
	// Message and Score
	int score = 0;

	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	Text messageText;
	Text scoreText;
	messageText.setFont(font);
	scoreText.setFont(font);
	messageText.setString("Use <- and -> to move\n x to grab and c to release the balls\nPress Enter to start!");
	scoreText.setString("Score = 0");
	messageText.setCharacterSize(15);
	scoreText.setCharacterSize(15);
	messageText.setFillColor(Color::Red);
	scoreText.setFillColor(Color::Red);

	// Position the text 
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(windowsResolution.x / 2.0f, windowsResolution.y / 2.0f);

	scoreText.setPosition(20, 20);

	// Player Input
	bool acceptInput = false;

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !isPaused)
			{
				// Listen for key presses again 
				acceptInput = true;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			isPaused = false;
			score = 0;

			acceptInput = true;
		}

		if(acceptInput)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				if(playerCurrentPosition > 0) playerCurrentPosition--;
				character.move(leftBorder + playerCurrentPosition*playerWidth, bottomBorder);
				characterActionState = CharacterState::LEFT;
				acceptInput = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (playerCurrentPosition < matrixDimensions.x - 1) playerCurrentPosition++;
				character.move(leftBorder + playerCurrentPosition*playerWidth, bottomBorder);
				characterActionState = CharacterState::RIGHT;
				acceptInput = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::X))
			{
				crystalHolder.trasferCrystalFromMatrix(0, &matrix, playerCurrentPosition);
				characterActionState = CharacterState::ACTION;
				acceptInput = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::C))
			{
				matrix.trasferCrystalFromMatrix(playerCurrentPosition, &crystalHolder, 0);
				characterActionState = CharacterState::ACTION;
				acceptInput = false;
			}
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!isPaused)
		{
			// Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		window.clear();

		window.draw(background.getSprite());
		matrix.drawMatrix(window);
		crystalHolder.drawMatrix(window);
		window.draw(character.getNextFrame(.15, characterActionState));

		if (!isPaused)
			window.draw(scoreText);
		else
			window.draw(messageText);

		window.display();
	}

	return 0;
}