﻿#pragma comment(lib,"Winmm.lib")

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

	// Load a sprite to display
	const sf::Texture texture("./resources/player.png");
	sf::Sprite sprite(texture);
	sprite.scale({0.1, 0.1});


	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		while (const std::optional event = window.pollEvent())
		{
			// Close window: exit
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		// Clear screen
		window.clear();

		// Draw the sprite
		window.draw(sprite);


		// Update the window
		window.display();
	}
}
