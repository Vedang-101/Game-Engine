#pragma once

#include "rendererable2d.h"
#include "../textures/spritesheet.h"

namespace rse {
	namespace graphics {

		class Sprite : public Renderable2D {
		private:

		public:
			Sprite(maths::vec2 position, maths::vec2 scale, const float rotation, const unsigned int color);
			Sprite(maths::vec2 position, maths::vec2 scale, const float rotation, Texture* texture);
			Sprite(maths::vec2 position, maths::vec2 scale, const float rotation, const unsigned int color, Texture* texture);
			Sprite(maths::vec2 position, maths::vec2 scale, const float rotation, SpriteSheet* spriteSheet, int index);
		};

	}
}