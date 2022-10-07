#pragma once

#include "../../utils/glerror.h"
#include "../../utils/imageload.h"
#include <string>
#include <GL/glew.h>

namespace rse {
	namespace graphics {

		class Texture {
		protected:
			std::string m_FileName;
			GLuint m_TID;
			GLsizei m_Width, m_Height;
		public:
			Texture(const std::string& filename);
			~Texture();

			void bind() const;
			void unbind() const;

			inline const unsigned int getWidth() { return m_Width; }
			inline const unsigned int getHeight() { return m_Height; }
			inline const unsigned int getID() { return m_TID; }
			virtual inline void getUV(int index, float *x, float *y, float *w, float *h) { *x = 0; *y = 0; *w = 1; *h = 1; }
		private:
			GLuint load();
		};

	}
}