#include "layer.h"

namespace rse {
	namespace graphics {

		GLint Layer::m_TexID[RENDERER_TEXTURE_SLOTS];

		Layer::Layer(Camera* camera, Shader *shader)
			:m_Camera(camera), m_Shader(shader)
		{
			for (int i = 0; i < RENDERER_TEXTURE_SLOTS; i++)
			{
				m_TexID[i] = i;
			}

			m_Shader->enable();
			m_Shader->SetUniformMat4("pr_matrix", m_Camera->getProjection());
			m_Shader->SetUniform1iv("textures", RENDERER_TEXTURE_SLOTS, m_TexID);
			m_Shader->disable();
		}

		Layer::~Layer() {
			for (unsigned int i = 0; i < m_Renderables.size(); i++)
				if(m_Renderables[i])
					delete m_Renderables[i];
		}

		unsigned int Layer::add(Renderable2D *gameobject) {
			m_Renderables.push_back(gameobject);
			return m_Index++;
		}

		void Layer::render() {
			m_Shader->enable();
			m_Shader->SetUniformMat4("vw_matrix", m_Camera->getTransform());

			m_Camera->getRenderer()->begin();

			for (Renderable2D* renderable : m_Renderables)
				renderable->submit(m_Camera->getRenderer());

			m_Camera->getRenderer()->end();

			m_Camera->getRenderer()->flush();
		}

	}
}