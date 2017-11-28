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

const Vector2u windowsResolution(800, 600);
const Vector2u matrixDimensions(15, 10);
unsigned int playerCurrentPosition = 0;

int main()
{
	// Create a video mode object 
	VideoMode vm(windowsResolution.x, windowsResolution.y);

	// Create and open a window for the game 
	RenderWindow window(vm, "CommonDrops", Style::Fullscreen);

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

	// Make a crystals sprite
	Crystal::initializeClass();
	CrystalMatrix matrix(Vector2u(100, 50), matrixDimensions);

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

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

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
				acceptInput = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (playerCurrentPosition < matrixDimensions.x - 1) playerCurrentPosition++;
				acceptInput = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::X))
			{
				matrix.destroyCrystalInCol(playerCurrentPosition);
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

		if (!isPaused)
			window.draw(scoreText);
		else
			window.draw(messageText);

		window.display();
	}

	return 0;
}