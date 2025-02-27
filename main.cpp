#pragma comment(lib,"Winmm.lib")

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
	window.setFramerateLimit(60);
	// Load a sprite to display
	const sf::Texture texture("./resources/player.png");
	sf::Sprite sprite(texture);
	sprite.scale({0.1, 0.1});
	int degree = 0;

	sf::Vector2<float> location{150.0f, 150.0f};

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
		sprite.setRotation(sf::degrees(degree));
		degree++;
		//location += {1, 1};
		sprite.setPosition(location);

		// Clear screen
		window.clear(sf::Color::White);

		// Draw the sprite
		window.draw(sprite);


		// Update the window
		window.display();
	}
}
