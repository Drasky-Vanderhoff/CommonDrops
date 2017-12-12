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
#include "Map.h"

using namespace sf;


const Vector2u windowsResolution(800, 600);
const Vector2u matrixDimensions(15, 15);
const float playerWidth = 32.0f;
const unsigned int leftBorder = 100;
const unsigned int rightBorder = windowsResolution.x - 64;
const unsigned int topBorder = 50;
const unsigned int bottomBorder = 480;
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
	textureBackground.loadFromFile("graphics/backgrounds/city-ruins.png");

	Texture textureTiles;
	textureTiles.loadFromFile("graphics/tilemaps/tiles-stones.png");
	Map map(textureBackground, textureTiles, Vector2i(64, 64), TilesPositionsType({
		Vector3i(9,0,12),
		Vector3i(9,1,13),
		Vector3i(9,2,13),
		Vector3i(9,3,13),
		Vector3i(9,4,13),
		Vector3i(9,5,13),
		Vector3i(9,6,13),
		Vector3i(9,7,14),		
		Vector3i(10,0,16),
		Vector3i(10,1,17),
		Vector3i(10,2,17),
		Vector3i(10,3,17),
		Vector3i(10,4,17),
		Vector3i(10,5,17),
		Vector3i(10,6,17),
		Vector3i(10,7,18),
		Vector3i(0,8,5),
		Vector3i(1,8,10),
		Vector3i(2,8,6),
		Vector3i(3,8,10),
		Vector3i(4,8,6),
		Vector3i(5,8,10),
		Vector3i(6,8,6),
		Vector3i(7,8,10),
		Vector3i(8,8,6),
		Vector3i(9,8,10),
		Vector3i(10,8,6),
		Vector3i(11,8,10),
		Vector3i(12,8,9),
		Vector3i(0,9,14),
		Vector3i(1,9,15),
		Vector3i(2,9,19),
		Vector3i(3,9,15),
		Vector3i(4,9,19),
		Vector3i(5,9,15),
		Vector3i(6,9,19),
		Vector3i(7,9,15),
		Vector3i(8,9,19),
		Vector3i(9,9,15),
		Vector3i(10,9,19),
		Vector3i(11,9,15),
		Vector3i(12,9,18)
	}));

	// Make a crystals matrix
	Crystal::initializeClass();
	CrystalMatrix matrix(Vector2u(leftBorder, topBorder), matrixDimensions);

	// Make player crystal holder
	Player player = Player("graphics/character/green-bot.png",
						   Vector2u(leftBorder, bottomBorder + 4),
						   matrixDimensions.x - 1,
						   Vector2u(rightBorder, topBorder),
						   matrixDimensions.y,
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

		map.render(&window);
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