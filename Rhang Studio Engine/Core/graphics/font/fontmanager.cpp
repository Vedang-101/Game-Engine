#include "fontmanager.h"

namespace rse{
	namespace graphics {
		std::vector<Font*> FontManager::m_Fonts;

		void FontManager::add(Font* font) {
			m_Fonts.push_back(font);
		}

		Font& FontManager::get(const std::string& name) {
			for (Font* font : m_Fonts)
				if (font->getName() == name)
					return *font;
			utils::LogWarning("Could not find specified font, using default font instead.");
			return *m_Fonts[0];
		}

		Font& FontManager::get(const std::string& name, unsigned int size) {
			for (Font* font : m_Fonts)
				if (font->getSize() == size && font->getName() == name)
					return *font;
			utils::LogWarning("Could not find specified font, using default font instead.");
			return *m_Fonts[0];
		}
		
		void FontManager::clean() {
			for (int i = 0; i < m_Fonts.size(); i++)
				delete m_Fonts[i];
		}
	}
}