#pragma once

#include "rendererable2d.h"
#include "../font/fontmanager.h"

namespace rse {
	namespace graphics {

		class Label : public Renderable2D {
		private:
			std::string m_Text;
			const Font* m_Font;
		public:
			Label(std::string text, float x, float y, const Font& font, float size, unsigned int color);
			Label(std::string text, float x, float y, const std::string& font, float size, unsigned int color);
			void submit(Renderer2D* renderer) const override;

			std::string getText() { return m_Text; }
			void setText(const std::string& text) { m_Text = text; }
			void setFont(const std::string& font) { m_Font = &FontManager::get(font); }
			void setFont(const Font& font) { m_Font = &font; }
		};

	}
}