#include "RenderComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "GameObject.h"
#include "TransformComponent.h"
#include "EffectComponent.h"

namespace psh::component
{
	RenderComponent::RenderComponent(const std::string& texturePath): m_texture(texturePath)
	{
		// Set origin to center of texture
		const auto textureSize = static_cast<sf::Vector2f>(m_texture.getSize());
	}

	void RenderComponent::Initialize()
	{
		m_transform = GetOwner()->GetRequiredComponent<TransformComponent>();
		m_effect = GetOwner()->GetComponent<EffectComponent>();
		m_transform->GetShape()->setTexture(&m_texture);
	}

	void RenderComponent::Update(MsTime deltaTime)
	{
	}

	void RenderComponent::Draw(sf::RenderWindow& window) const
	{
		window.draw(*m_transform->GetShape());
		if (m_effect)
		{
			m_effect->Draw(window);
		}
	}
}
