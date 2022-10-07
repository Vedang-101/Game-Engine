#pragma once

#include "../renderers/renderer2d.h"
#include "../renderables/rendererable2d.h"
#include "../camera.h"

namespace rse {
	namespace graphics {

		class Layer {
		protected:
			Camera* m_Camera;
			std::vector<Renderable2D*> m_Renderables;
			Shader *m_Shader;
			unsigned int m_Index;
			static GLint m_TexID[RENDERER_TEXTURE_SLOTS];
		protected:
			Layer(Camera* camera, Shader *shader);
		public:
			virtual ~Layer();
			virtual unsigned int add(Renderable2D *renderable);
			virtual void render();

			inline Renderable2D* getRenderable(int index) const { return m_Renderables[index]; }
			inline const std::vector<Renderable2D*>& getRenderables() const { return m_Renderables; }
		};

	}
}