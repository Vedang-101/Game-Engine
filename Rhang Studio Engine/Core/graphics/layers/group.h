#pragma once

#include "../renderables/rendererable2d.h"

namespace rse {
	namespace graphics {

		class Group : public Renderable2D {
		private:
			std::vector<Renderable2D *> m_Renderables;
			maths::mat4 m_TransformationMatrix;
			unsigned int m_index;
		public:
			Group(const maths::mat4& transform);
			~Group();

			unsigned int add(Renderable2D* renderable);
			void submit(Renderer2D* renderer) const override;

			inline Renderable2D* getRenderable(int index) const { return m_Renderables[index]; }
			inline const std::vector<Renderable2D*>& getRenderables() const { return m_Renderables; }
		};

	}
}