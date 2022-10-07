#pragma once

#include "texture.h"

namespace rse {
	namespace graphics {
		class SpriteSheet :public Texture {
		private:
			int m_Rows;
			int m_Columns;
		public:
			SpriteSheet(const std::string& filename, int rows, int columns)
				:Texture(filename), m_Rows(rows), m_Columns(columns)
			{ }

			inline void getUV(int index, float *x, float *y, float *w, float *h) override {
				*w = 1 / (float)m_Columns;
				*h = 1 / (float)m_Rows;
				*x = (index % m_Columns) * (*w);
				*y = 1 - ((int)((index / m_Columns) + 1) * (*h));
			}

		};
	}
}