#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "RenderComponent.hpp"
#include "InputComponent.hpp"
#include <chrono>

class GameManager {
public:
    GameManager() : m_Window(sf::VideoMode({800, 600}), "SFML Component Game") {
        m_LastFrameTime = std::chrono::high_resolution_clock::now();
    }

    void Initialize() {
        // Create player object
        auto player = std::make_shared<GameObject>("Player");
        auto transform = player->AddComponent<TransformComponent>(sf::Vector2f(150.0f, 150.0f));
        transform->SetScale(sf::Vector2f(0.1f, 0.1f));
        
        auto renderer = player->AddComponent<RenderComponent>("./resources/player.png");
        player->AddComponent<InputComponent>();
        
        player->Initialize();
        m_GameObjects.push_back(player);
    }

    void Run() {
        while (m_Window.isOpen()) {
            // Calculate delta time
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - m_LastFrameTime).count();
            m_LastFrameTime = currentTime;

            // Process events
            sf::Event event;
            while (m_Window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_Window.close();
                
                // Pass events to input components
                for (auto& gameObject : m_GameObjects) {
                    auto inputComponent = gameObject->GetComponent<InputComponent>();
                    if (inputComponent) {
                        inputComponent->HandleEvent(event);
                    }
                }
            }

            // Update all game objects
            for (auto& gameObject : m_GameObjects) {
                gameObject->Update(deltaTime);
            }

            // Render
            m_Window.clear(sf::Color::White);
            
            for (auto& gameObject : m_GameObjects) {
                auto renderComponent = gameObject->GetComponent<RenderComponent>();
                if (renderComponent) {
                    renderComponent->Draw(m_Window);
                }
            }
            
            m_Window.display();
        }
    }

private:
    sf::RenderWindow m_Window;
    std::vector<std::shared_ptr<GameObject>> m_GameObjects;
    std::chrono::high_resolution_clock::time_point m_LastFrameTime;
};
