// HelloSFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "Renderable.h"
#include "Animatable.h"
#include "CrystalMatrix.h"
#include "Player.h"

using namespace sf;


const Vector2u windowsResolution(800, 600);
const Vector2u matrixDimensions(15, 15);
const float playerWidth = 32.0f;
const unsigned int leftBorder = 100;
const unsigned int rightBorder = windowsResolution.x - 64;
const unsigned int topBorder = 50;
const unsigned int bottomBorder = 500;
const unsigned int playerMovementsPeak = 10;

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

	// Make player crystal holder
	Player player = Player("graphics/character/green-bot.png",
						   Vector2u(leftBorder, bottomBorder),
						   matrixDimensions.x,
						   Vector2u(rightBorder, topBorder),
						   matrixDimensions.x,
						   &matrix
						   );
	CrystalMatrix crystalHolder();
	
	// Message and Score
	unsigned int score = 0;

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

	messageText.setOrigin(textRect.left + textRect.width / 2.0f,
						  textRect.top + textRect.height / 2.0f);

	messageText.setPosition(windowsResolution.x / 2.0f, windowsResolution.y / 2.0f);

	scoreText.setPosition(20, 20);

	// Player Input
	bool acceptInput = false;
	unsigned int playerMovements = 0;
	bool gameOver = false;

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players actions
		****************************************
		*/

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !isPaused)
			{
				// Listen for key presses again 
				playerMovements++;
				acceptInput = true;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			isPaused = false;
			score = 0;

			acceptInput = true;
			matrix.fillMatrixWithRandomCrystals();
		}

		if (gameOver) {
			isPaused = true;
			acceptInput = false;
			gameOver = false;
			messageText.setString("You lost!!!\nPress Enter to start!");
		}

		if (acceptInput) acceptInput = player.processEvents(&gameOver, &score);

		if (playerMovements >= playerMovementsPeak) {
			playerMovements = 0;
			gameOver = matrix.addRandomCrystalRowToMatrix();
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
		player.drawPlayer(window);

		if (!isPaused)
			window.draw(scoreText);
		else
			window.draw(messageText);

		window.display();
	}

	return 0;
}