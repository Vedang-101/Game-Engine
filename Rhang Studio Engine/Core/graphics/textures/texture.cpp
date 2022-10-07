#include "texture.h"

namespace rse {
	namespace graphics {
		Texture::Texture(const std::string& filename)
			: m_FileName(filename)
		{
			m_TID = load();
		}

		Texture::~Texture() {

		}

		void Texture::bind() const {
			glBindTexture(GL_TEXTURE_2D, m_TID);
		}

		void Texture::unbind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		GLuint Texture::load() {
			int bitsperpixels;
			BYTE* pixels = utils::load_image(m_FileName.c_str(), &m_Width, &m_Height, &bitsperpixels);

			GLuint result;
			GLCall(glGenTextures(1, &result));
			GLCall(glBindTexture(GL_TEXTURE_2D, result));

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

			if (bitsperpixels == 24) {
				GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels));
			}
			else {
				GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels));
			}

			GLCall(glBindTexture(GL_TEXTURE_2D, 0));

			delete[] pixels;

			return result;
		}
	}
}