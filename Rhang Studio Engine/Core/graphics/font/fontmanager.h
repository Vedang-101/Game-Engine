#pragma once

#include "../../utils/logger.h"
#include "font.h"
#include <vector>

namespace rse {
	namespace graphics {
		class FontManager {
		private:
			static std::vector<Font*> m_Fonts;
		public:
			static void add(Font* font);
			static Font& get(const std::string& name);
			static Font& get(const std::string& name, unsigned int size);
			static void clean();
		private:
			FontManager();
		};
	}
}