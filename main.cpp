#pragma comment(lib,"Winmm.lib")

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
	sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

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

				// 부드러운 회전을 위해 현재 각도와 목표 각도 사이를 보간
				float currentAngle = sprite.getRotation();
				float rotationSpeed = 5.0f; // 회전 속도
				float deltaAngle = angle - currentAngle;

				// 가장 짧은 회전 방향을 결정
				if (deltaAngle > 180.0f) deltaAngle -= 360.0f;
				if (deltaAngle <= -180.0f) deltaAngle += 360.0f;

				float newAngle = currentAngle + deltaAngle * rotationSpeed * 0.1f; // 0.1f는 프레임 간 시간 간격을 조절하기 위한 값
				sprite.setRotation(newAngle);
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
