#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "RenderComponent.hpp"
#include "InputComponent.hpp"
#include <chrono>

#include "Event.h"

namespace psh
{
	enum class InputEvent
	{
		KeyPressed,
	};
}

class GameManager
{
public:
	GameManager() : m_Window(sf::VideoMode({800, 600}), "SFML Component Game")
	{
		m_LastFrameTime = std::chrono::high_resolution_clock::now();
	}

	void Initialize()
	{
		// Create player object
		auto player = std::make_shared<GameObject>("Player");
		auto transform = player->AddComponent<TransformComponent>(sf::Vector2f(150.0f, 150.0f));
		transform->SetScale(sf::Vector2f(0.1f, 0.1f));

		auto renderer = player->AddComponent<RenderComponent>("./resources/player.png");
		player->AddComponent<InputComponent>();

		player->Initialize();
		m_GameObjects.push_back(player);
	}


	void Run()
	{
		while (m_Window.isOpen())
		{
			// Calculate delta time
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - m_LastFrameTime).count();
			m_LastFrameTime = currentTime;

			// Process events
			while (auto event = m_Window.pollEvent())
			{
				event->visit([this](auto&& value)
				{
					using T = std::decay_t<decltype(value)>;

					if constexpr (std::is_same_v<T, sf::Event::Closed>)
					{
						m_Window.close();
					}
					else if constexpr (std::is_same_v<T, sf::Event::KeyPressed>)
					{
						std::cout << "Key pressed: " << static_cast<int>(value.code) << "\n";
					}
				});
			}

			// Update all game objects
			for (auto& gameObject : m_GameObjects)
			{
				gameObject->Update(deltaTime);
			}

			// Render
			m_Window.clear(sf::Color::White);

			for (auto& gameObject : m_GameObjects)
			{
				auto renderComponent = gameObject->GetComponent<RenderComponent>();
				if (renderComponent)
				{
					renderComponent->Draw(m_Window);
				}
			}

			m_Window.display();
		}
	}

private:
	std::chrono::milliseconds startTime_;
	sf::RenderWindow m_Window;
	std::vector<std::shared_ptr<GameObject>> m_GameObjects;
	std::chrono::high_resolution_clock::time_point m_LastFrameTime;

	EventSystem::EventManager<psh::InputEvent> m_eventManager;
};
