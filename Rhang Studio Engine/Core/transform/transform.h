#pragma once

#include "../maths/maths.h"

namespace rse {
	namespace transform {
		struct Transform {
			maths::vec3 position;
			float rotation;
			maths::vec3 size;
			maths::mat4 transformMatrix;

			Transform() { transformMatrix.updateTransform(position, rotation, size); }

			Transform(maths::vec3 position, float rotation, maths::vec3 size) {
				this->position = position;
				this->rotation = rotation;
				this->size = size;
				transformMatrix.updateTransform(position, rotation, size);
			}

			inline void setPosition(const maths::vec3 position) {
				this->position = position;
				transformMatrix.updateTransform(this->position, rotation, size);
			}

			inline void setRotation(const float angle) {
				this->rotation = angle;
				transformMatrix.updateTransform(position, rotation, size);
			}

			inline void setScale(const maths::vec3 scale) {
				this->size = scale;
				transformMatrix.updateTransform(position, rotation, size);
			}
		};
	}
}