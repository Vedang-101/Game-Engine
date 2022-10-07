#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "maths_func.h"

namespace rse {
	namespace maths {
		
		struct mat4 {
			union {
				float elements[4 * 4];
				vec4 columns[4];
			};

			mat4();
			mat4(float diagonal);

			static mat4 identity();

			mat4& multiply(const mat4& other);
			friend mat4 operator*(mat4 left, const mat4& right);
			mat4& operator*=(const mat4& other);

			mat4& invert();

			vec4 multiply(const vec4& other) const;
			friend vec4 operator*(const mat4& left, const vec4& right);

			vec3 multiply(const vec3& other) const;
			friend vec3 operator*(const mat4& left, const vec3& right);

			static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 perspective(float fov, float aspectRatio, float near, float far);

			static mat4 translation(const vec3& translation);
			static mat4 rotation(float angle);
			static mat4 scale(const vec3& scale);

			static mat4 transform(const vec3& translation, float angle, const vec3& scale);
			void updateTransform(const vec3& translation, float angle, const vec3& scale);
		};

	}
}