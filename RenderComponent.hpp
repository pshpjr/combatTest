#pragma once
#include "Component.hpp"
#include "TransformComponent.hpp"
#include <SFML/Graphics.hpp>

class RenderComponent : public Component
{
public:
	RenderComponent(const std::string& texturePath): m_Texture(texturePath), m_Sprite(m_Texture)
	{
		// Set origin to center of texture
		const auto textureSize = static_cast<sf::Vector2f>(m_Texture.getSize());
		m_Sprite.setOrigin({textureSize.x / 2.0f, textureSize.y / 2.0f});
	}

	void Initialize() override
	{
		m_Transform = GetOwner()->GetComponent<TransformComponent>();
		if (!m_Transform)
		{
			throw std::runtime_error("RenderComponent requires a TransformComponent");
		}
	}

	void Update(float deltaTime) override
	{
		if (m_Transform)
		{
			m_Sprite.setPosition(m_Transform->GetPosition());
			m_Sprite.setRotation(m_Transform->GetRotation());
			m_Sprite.setScale(m_Transform->GetScale());
		}
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(m_Sprite);
	}

	sf::Sprite& GetSprite()
	{
		return m_Sprite;
	}

	const sf::Sprite& GetSprite() const
	{
		return m_Sprite;
	}

private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	TransformComponent* m_Transform;
	TYPEID_DEFINE("Render")
};
