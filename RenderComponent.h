#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Component.h"


namespace sf
{
	class RenderWindow;
}


namespace psh::component
{
	class TransformComponent;
	class EffectComponent;

	class RenderComponent : public Component
	{
	public:
		explicit RenderComponent(const std::string& texturePath);

		void Initialize() override;

		void Update(MsTime deltaTime) override;

		void Draw(sf::RenderWindow& window) const;

	private:
		sf::Texture m_texture;
		TransformComponent* m_transform{nullptr};
		EffectComponent* m_effect{nullptr};
		COMPONENT_DEFINE("Render")
	};
}
