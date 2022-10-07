#pragma once

#include <string>
#include <FreeImage.h>
#include <GL/glew.h>

namespace rse {
	namespace utils {

		static BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height, int* bitsperpixel) {

			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			fif = FreeImage_GetFileType(filename, 0);
			FIBITMAP* dib = nullptr;
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(filename);
			if (fif == FIF_UNKNOWN)
				return nullptr;

			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, filename);
			if (!dib)
				return nullptr;

			BYTE *pixels = FreeImage_GetBits(dib);

			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);

			*bitsperpixel = FreeImage_GetBPP(dib);
			const int size = (*width) * (*height) * (*bitsperpixel) / 8;
			BYTE *result = new BYTE[size];
			memcpy(result, pixels, size);

			FreeImage_Unload(dib);

			return result;
		}
	}
}