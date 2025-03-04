#include "GameManager.h"

#include "InputComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "Time.h"
#include "TransformComponent.h"

namespace psh
{
	using TransformComponent = component::TransformComponent;
	using RenderComponent = component::RenderComponent;
	using InputComponent = component::InputComponent;

	GameManager::GameManager() : m_window(sf::VideoMode({1920, 1080}), "SFML component Game")
	{
	}

	void GameManager::Initialize()
	{
		// Create player object
		const auto player = std::make_shared<GameObject>(static_cast<GUID>(1));
		const auto transform = player->AddComponent<TransformComponent>(sf::Vector2f(150.0f, 150.0f), sf::degrees(0),
		                                                                true);

		player->AddComponent<RenderComponent>("./resources/Mage.png");
		player->AddComponent<component::MovementComponent>();
		auto input = player->AddComponent<InputComponent>();
		player->Initialize();

		transform->SetSize(sf::Vector2f(100, 100));
		transform->SetPosition({500, 500});
		auto mouseEvent = m_eventManager.GetOrCreateEvent<InputType, sf::Event*>(GameEvent::InputEvent);
		mouseEvent.Subscribe([input](InputType type, sf::Event* e)
		{
			input->HandleEvent(type, e);
		});


		m_gameObjects.push_back(player);
	}

	void GameManager::Render()
	{
		m_window.clear(sf::Color::White);
		for (const auto& gameObject : m_gameObjects)
		{
			if (const auto renderComponent = gameObject->GetComponent<RenderComponent>())
			{
				renderComponent->Draw(m_window);
			}
		}
		m_window.display();
	}

	void GameManager::HandleInput()
	{
		while (auto event = m_window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				m_window.close();
			}
			else if (event->is<sf::Event::KeyPressed>())
			{
				m_eventManager.Notify(GameEvent::InputEvent, InputType::Keyboard, &event.value());
			}
			else if (event->is<sf::Event::MouseButtonPressed>())
			{
				m_eventManager.Notify(GameEvent::InputEvent, InputType::Mouse, &event.value());
			}
		}
	}

	constexpr MsTime FIXED_UPDATE_TIME = 20;
	MsTime physicsUpdateRemain = 0;

	void GameManager::Update(MsTime diff)
	{
		physicsUpdateRemain += diff;
		while (physicsUpdateRemain >= FIXED_UPDATE_TIME)
		{
			for (const auto& gameObject : m_gameObjects)
			{
				gameObject->Update(FIXED_UPDATE_TIME);
			}
			physicsUpdateRemain -= FIXED_UPDATE_TIME;
		}
	}

	void GameManager::Run()
	{
		m_prevServerTime = getMSTime();
		m_nextUpdateTime = m_prevServerTime + FIXED_UPDATE_TIME;
		sf::Shape* c = new sf::CircleShape(0);

		auto texture = new sf::Texture("./resources/Mage.png");
		c->setTexture(texture);

		static_cast<sf::CircleShape*>(c)->setRadius(10);
		c->setOrigin({10, 10});
		c->setPosition({600, 600});

		std::cout << "Texture Size: " << texture->getSize().x << "x" << texture->getSize().y << std::endl;
		while (m_window.isOpen())
		{
			m_serverTime = getMSTime();

			if (m_serverTime >= m_nextUpdateTime)
			{
				const uint32 diff = getMSTimeDiff(m_prevServerTime, GetServerTime());

				UpdateFrameStats(diff);
				// Process events
				HandleInput();

				// Update all game objects
				Update(FIXED_UPDATE_TIME);

				// Render
				Render();


				m_nextUpdateTime += FIXED_UPDATE_TIME;
				m_prevServerTime = m_serverTime;
			}
			else
			{
				auto sleepTime = m_nextUpdateTime - m_serverTime;
				std::this_thread::sleep_for(Milliseconds(sleepTime));
			}
		}
	}

	uint32 GameManager::GetServerTime() const
	{
		return m_serverTime;
	}

	void GameManager::UpdateFrameStats(MsTime frameTime)
	{
		m_frameTimeAccumulator += frameTime;
		m_frameCount++;

		// Update min/max frame times
		m_minFrameTime = std::min(m_minFrameTime, frameTime);
		m_maxFrameTime = std::max(m_maxFrameTime, frameTime);

		// Update FPS every FPS_UPDATE_INTERVAL milliseconds
		if (m_frameTimeAccumulator >= FPS_UPDATE_INTERVAL)
		{
			m_fps = static_cast<float>(m_frameCount) * 1000.f / m_frameTimeAccumulator;
			m_averageFrameTime = m_frameTimeAccumulator / m_frameCount;
			std::cout << m_fps << "\n";
			// Reset counters
			m_frameTimeAccumulator = 0;
			m_frameCount = 0;
			m_minFrameTime = std::numeric_limits<MsTime>::max();
			m_maxFrameTime = 0;
		}
	}
}
