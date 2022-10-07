#include "sprite.h"

namespace rse {
	namespace graphics {

		Sprite::Sprite(maths::vec2 position, maths::vec2 scale, const float rotation, const unsigned int color) {
			m_Transform.position = maths::vec3(position.x, position.y, 0);
			m_Transform.rotation = rotation;
			m_Transform.size = maths::vec3(scale.x, scale.y, 1);
			m_Transform.transformMatrix = maths::mat4::transform(m_Transform.position, m_Transform.rotation, m_Transform.size);
			m_Color = color;
		}

		Sprite::Sprite(maths::vec2 position, maths::vec2 scale, const float rotation, Texture* texture) {
			m_Transform.position = maths::vec3(position.x, position.y, 0);
			m_Transform.rotation = rotation;
			m_Transform.size = maths::vec3(scale.x, scale.y, 1);
			m_Transform.transformMatrix = maths::mat4::transform(m_Transform.position, m_Transform.rotation, m_Transform.size);
			m_Color = 0xffffffff;
			m_Texture = texture;
		}

		Sprite::Sprite(maths::vec2 position, maths::vec2 scale, const float rotation, const unsigned int color, Texture* texture) {
			m_Transform.position = maths::vec3(position.x, position.y, 0);
			m_Transform.rotation = rotation;
			m_Transform.size = maths::vec3(scale.x, scale.y, 1);
			m_Transform.transformMatrix = maths::mat4::transform(m_Transform.position, m_Transform.rotation, m_Transform.size);
			m_Color = color;
			m_Texture = texture;
		}

		Sprite::Sprite(maths::vec2 position, maths::vec2 scale, const float rotation, SpriteSheet* spriteSheet, int index) {
			m_Transform.position = maths::vec3(position.x, position.y, 0);
			m_Transform.rotation = rotation;
			m_Transform.size = maths::vec3(scale.x, scale.y, 1);
			m_Transform.transformMatrix = maths::mat4::transform(m_Transform.position, m_Transform.rotation, m_Transform.size);
			m_Color = 0xffffffff;
			m_Texture = spriteSheet;
			setSprite(index);
		}

	}
}