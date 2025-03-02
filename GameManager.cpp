#include "GameManager.h"

#include "InputComponent.hpp"
#include "RenderComponent.hpp"
#include "Time.h"
#include "TransformComponent.hpp"

GameManager::GameManager(): m_window(sf::VideoMode({800, 600}), "SFML Component Game")
{
	m_lastFrameTime = std::chrono::high_resolution_clock::now();
}

void GameManager::Initialize()
{
	// Create player object
	const auto player = std::make_shared<GameObject>(static_cast<GUID>(1));
	const auto transform = player->AddComponent<TransformComponent>(sf::Vector2f(150.0f, 150.0f));
	transform->SetScale(sf::Vector2f(0.1f, 0.1f));

	player->AddComponent<RenderComponent>("./resources/player.png");
	auto input = player->AddComponent<InputComponent>();
	player->Initialize();

	auto mouseEvent = m_eventManager.GetOrCreateEvent<psh::InputEvent, sf::Event*>(psh::InputEvent::MousePressed);
	mouseEvent.Subscribe([input](psh::InputEvent type, sf::Event* e)
	{
		input->HandleEvent(type, e);
	});


	m_gameObjects.push_back(player);
}

void GameManager::Run()
{
	m_prevServerTime = getMSTime();


	while (m_window.isOpen())
	{
		m_serverTime = getMSTime();

		const uint32 diff = getMSTimeDiff(m_prevServerTime, GetServerTime());

		if (diff < kMIN_UPDATE_TIME)
		{
			uint32 sleepTime = kMIN_UPDATE_TIME - diff;
			std::this_thread::sleep_for(Milliseconds(sleepTime));
			continue;
		}

		// Process events
		while (auto event = m_window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				m_window.close();
			}
			else if (event->is<sf::Event::KeyPressed>())
			{
				m_eventManager.Notify(psh::InputEvent::MousePressed, psh::InputEvent::KeyPressed, &event.value());
			}
			else if (event->is<sf::Event::MouseButtonPressed>())
			{
				m_eventManager.Notify(psh::InputEvent::MousePressed, psh::InputEvent::MousePressed, &event.value());
			}
		}

		// Update all game objects
		for (const auto& gameObject : m_gameObjects)
		{
			gameObject->Update(diff);
		}

		// Render
		m_window.clear(sf::Color::White);

		for (const auto& gameObject : m_gameObjects)
		{
			if (const auto renderComponent = gameObject->GetComponent<RenderComponent>())
			{
				renderComponent->Draw(m_window);
			}
		}

		m_window.display();

		m_prevServerTime = m_serverTime;
	}
}

uint32 GameManager::GetServerTime() const
{
	return m_serverTime;
}
