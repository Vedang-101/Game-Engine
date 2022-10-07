#pragma once

#include "../../ext/freetype-gl/freetype-gl.h"
#include <string>

namespace rse {
	namespace graphics {
		class Font {
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			unsigned int m_Size;

			std::string m_Name;
			std::string m_FileName;
		public:
			Font(const std::string& name, const std::string& filename, int size);
			Font();

			inline const std::string& getName() const { return m_Name; }
			inline const std::string& getFileName() const { return m_FileName; }
			inline const int getSize() const { return m_Size; }
			inline const unsigned int getTID() const { return m_FTAtlas->id; }

			inline ftgl::texture_font_t* getFTfont() const { return m_FTFont; }
		};
	}
}