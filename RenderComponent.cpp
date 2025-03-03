#include "RenderComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"
#include "TransformComponent.h"

namespace psh::Component
{
	RenderComponent::RenderComponent(const std::string& texturePath): m_Texture(texturePath), m_Sprite(m_Texture),
	                                                                  m_Transform(nullptr)
	{
		// Set origin to center of texture
		const auto textureSize = static_cast<sf::Vector2f>(m_Texture.getSize());
		m_Sprite.setOrigin({textureSize.x / 2.0f, textureSize.y / 2.0f});
	}

	void RenderComponent::Initialize()
	{
		m_Transform = GetOwner()->GetComponent<TransformComponent>();
		if (!m_Transform)
		{
			throw std::runtime_error("RenderComponent requires a TransformComponent");
		}
	}

	void RenderComponent::Update(MsTime deltaTime)
	{
		if (m_Transform)
		{
			m_Sprite.setPosition(m_Transform->GetPosition());
			m_Sprite.setRotation(m_Transform->GetRotation());
			m_Sprite.setScale(m_Transform->GetScale());
		}
	}

	void RenderComponent::Draw(sf::RenderWindow& window) const
	{
		window.draw(m_Sprite);
	}

	sf::Sprite& RenderComponent::GetSprite()
	{
		return m_Sprite;
	}

	const sf::Sprite& RenderComponent::GetSprite() const
	{
		return m_Sprite;
	}
}
