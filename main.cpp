#pragma comment(lib,"Winmm.lib")

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
	window.setFramerateLimit(60);

	sf::Texture texture;
	if (!texture.loadFromFile("./resources/player.png"))
	{
		return -1;
	}

	sf::Sprite sprite(texture);
	sprite.scale({0.1f, 0.1f});

	// 텍스처 크기의 절반을 origin으로 설정
	auto textureSize = static_cast<sf::Vector2f>(texture.getSize());
	sprite.setOrigin({textureSize.x / 2.0f, textureSize.y / 2.0f});


	int degree = 0;
	sf::Vector2f location{150.0f, 150.0f};
	sprite.setPosition(location);


	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (event->is<sf::Event::MouseButtonPressed>())
			{
				auto value = event->getIf<sf::Event::MouseButtonPressed>();
				if (value->button != sf::Mouse::Button::Left)
				{
					continue;
				}

				sf::Vector2f clickPosition(value->position.x, value->position.y);

				// Calculate the angle between the sprite and the click position
				sf::Vector2f spritePosition = sprite.getPosition();
				float dx = clickPosition.x - spritePosition.x;
				float dy = clickPosition.y - spritePosition.y;
				float angle = std::atan2(dy, dx) * 180 / M_PI;

				sprite.setRotation(angle);
			}
		}

		//sprite.setRotation(sf::degrees(degree));
		//degree++;
		//sprite.setPosition(location);
		// 주석 처리: origin_point.setPosition(location); 
		// -> 더 이상 매 프레임마다 위치를 업데이트하지 않음

		window.clear(sf::Color::White);
		window.draw(sprite);
		window.display();
	}

	return 0;
}
