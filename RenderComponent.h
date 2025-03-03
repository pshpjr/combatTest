#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Component.h"

namespace sf
{
	class RenderWindow;
}


namespace psh::Component
{
	class TransformComponent;

	class RenderComponent : public Component
	{
	public:
		explicit RenderComponent(const std::string& texturePath);

		void Initialize() override;

		void Update(MsTime deltaTime) override;

		void Draw(sf::RenderWindow& window) const;

		sf::Sprite& GetSprite();

		const sf::Sprite& GetSprite() const;

	private:
		sf::Texture m_Texture;
		sf::Sprite m_Sprite;
		TransformComponent* m_Transform;
		TYPEID_DEFINE("Render")
	};
}
