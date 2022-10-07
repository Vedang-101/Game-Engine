#include "font.h"

namespace rse {
	namespace graphics {
		Font::Font()
			: m_Name("Arial"), m_FileName("res/fonts/arial.ttf"), m_Size(32)
		{
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, 32, "res/fonts/arial.ttf");
		}
		
		Font::Font(const std::string& name, const std::string& filename, int size)
			: m_Name(name), m_FileName(filename), m_Size(size)
		{
			//Optimal highest size of fonts to be packed in 512 * 512 texture sheet
			m_Size = m_Size > 72 ? 72 : m_Size;
			
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, size, filename.c_str());
		}
	}
}