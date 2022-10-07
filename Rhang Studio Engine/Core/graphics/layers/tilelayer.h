#pragma once

#include "layer.h"
#include "../camera.h"

namespace rse {
	namespace graphics {

		class TileLayer : public Layer {
		public:
			TileLayer(Camera* camera, Shader *shader)
				: Layer(camera, shader) { }

			~TileLayer() {}
		};

	}
}