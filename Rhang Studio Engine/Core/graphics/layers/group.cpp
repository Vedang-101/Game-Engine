#include "group.h"

namespace rse {
	namespace graphics {

		Group::Group(const maths::mat4& transform) : m_TransformationMatrix(transform), m_index(0) {}

		Group::~Group() {
			for (unsigned int i = 0; i < m_Renderables.size(); i++)
				if(m_Renderables[i])
					delete m_Renderables[i];
		}

		unsigned int Group::add(Renderable2D* renderable) {
			m_Renderables.push_back(renderable);
			return m_index++;
		}

		void Group::submit(Renderer2D* renderer) const {
			renderer->push(m_TransformationMatrix);
			for (const Renderable2D *renderable : m_Renderables) {
				renderable->submit(renderer);
			}
			renderer->pop();
		}
	}
}