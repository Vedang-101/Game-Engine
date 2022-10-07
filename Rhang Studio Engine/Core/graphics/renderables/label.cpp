#include "label.h"

namespace rse {
	namespace graphics {

		Label::Label(std::string text, float x, float y, const Font& font, float size, unsigned int color)
			: m_Text(text)
		{
			m_Transform.size = maths::vec3(size, size, 0);
			m_Transform.position = maths::vec3(x, y, 0);
			m_Color = color;
			m_Font = &font;
		}

		Label::Label(std::string text, float x, float y, const std::string& font, float size, unsigned int color)
			: m_Text(text)
		{
			m_Transform.size = maths::vec3(size, size, 0);
			m_Transform.position = maths::vec3(x, y, 0);
			m_Color = color;
			m_Font = &FontManager::get(font);
		}
		
		void Label::submit(Renderer2D* renderer) const {
			renderer->drawString(m_Text, m_Transform.position, m_Color, *m_Font, m_Transform.size.x);
		}

	}
}