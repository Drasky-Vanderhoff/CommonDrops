// HelloSFML.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <optional>
#include <inipp.h>
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
const unsigned int playerMovementsPeak = 20;

int main()
{
	inipp::Ini<char> ini;
	std::ifstream is("commondrops.ini");
	ini.parse(is);

	// Create a video mode object 
	VideoMode vm(windowsResolution);

	// Create and open a window for the game 
	std::string title;
	inipp::extract(ini.sections["DEFAULT"]["title"], title);
	RenderWindow window(vm, title, Style::Default);
	// Variable for update the scene
	Clock clock;
	bool isPaused = true;
	Animatable::initializeClass(&clock);

	//Sound and music
	Music music;
	std::string music_file;
	inipp::extract(ini.sections["DEFAULT"]["music"], music_file);
	music.openFromFile(music_file);

	SoundBuffer moveBuffer;
	std::string move_sFile;
	inipp::extract(ini.sections["DEFAULT"]["move_sound"], move_sFile);
	moveBuffer.loadFromFile(move_sFile);
	Sound move(moveBuffer);

	SoundBuffer catch_sBuffer;
	std::string catch_sFile;
	inipp::extract(ini.sections["DEFAULT"]["catch_sound"], catch_sFile);
	catch_sBuffer.loadFromFile(catch_sFile);
	Sound catch_s(catch_sBuffer);

	SoundBuffer throw_sBuffer;
	std::string throw_sFile;
	inipp::extract(ini.sections["DEFAULT"]["throw_sound"], throw_sFile);
	throw_sBuffer.loadFromFile(throw_sFile);
	Sound throw_s(throw_sBuffer);

	SoundBuffer combo_sBuffer;
	std::string combo_sFile;
	inipp::extract(ini.sections["DEFAULT"]["combo_sound"], combo_sFile);
	combo_sBuffer.loadFromFile(combo_sFile);
	Sound combo_s(combo_sBuffer);

	SoundBuffer newrowBuffer;
	std::string newrow_sFile;
	inipp::extract(ini.sections["DEFAULT"]["newrow_sound"], newrow_sFile);
	newrowBuffer.loadFromFile(newrow_sFile);
	Sound newrow(newrowBuffer);

	SoundBuffer gameOverBuffer;
	std::string gameOver_sFile;
	inipp::extract(ini.sections["DEFAULT"]["gameover_sound"], gameOver_sFile);
	gameOverBuffer.loadFromFile(gameOver_sFile);
	Sound gameOver_s(gameOverBuffer);

	
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
	CrystalMatrix matrix(Vector2u(leftBorder, topBorder), matrixDimensions , &combo_s, &newrow);

	// Make player crystal holder
	Player player = Player("graphics/character/green-bot.png",
						   Vector2u(leftBorder, bottomBorder + 4),
						   matrixDimensions.x - 1,
						   Vector2u(rightBorder, topBorder),
						   matrixDimensions.y,
						   &matrix,
						   &move,
						   &catch_s,
						   &throw_s);
	
	// Message and Score
	unsigned int score = 0;

	Font font;

	if (!font.openFromFile("fonts/KOMIKAP_.ttf"))
	{
		std::cerr << "Failed to load fonts/KOMIKAP_.ttf\n";
		return 1;
	}

	Text messageText(font);
	Text scoreText(font);
	messageText.setString("Use <- and -> to move\n x to grab and c to release the balls\nPress Enter to start!");
	scoreText.setString("Score = 0");
	messageText.setCharacterSize(15);
	scoreText.setCharacterSize(15);
	messageText.setFillColor(Color::Red);
	scoreText.setFillColor(Color::Red);

	// Position the text 
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(
		textRect.position + textRect.size / 2.0f
	);

	messageText.setPosition({
		windowsResolution.x / 2.0f,
		windowsResolution.y / 2.0f
	});

	scoreText.setPosition({20.0f, 20.0f});

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
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}
			else if (
				event->is<Event::KeyReleased>() &&
				!isPaused
			)
			{
				playerMovements++;
				acceptInput = true;
			}
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) window.close();

        if (isPaused && Keyboard::isKeyPressed(Keyboard::Key::Enter))
		{
			isPaused = false;
			score = 0;

			acceptInput = true;
			matrix.fillMatrixWithRandomCrystals();
			music.play();
		}

		if (gameOver) {
			isPaused = true;
			acceptInput = false;
			gameOver = false;
			messageText.setString("You lost!!!\nPress Enter to start!");
			gameOver_s.play();
			music.stop();
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
