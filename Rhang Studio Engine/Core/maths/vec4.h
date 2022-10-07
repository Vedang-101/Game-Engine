#pragma once
#include <iostream>
#include <math.h>

namespace rse {
	namespace maths {
		struct vec4 {

			union { float x, r; };
			union { float y, g; };
			union { float z, b; };
			union { float w, a; };

			vec4();
			vec4(const float& x, const float& y, const float& z, const float& w);

			vec4& add(const vec4& other);
			vec4& subtract(const vec4& other);
			vec4& multiply(const vec4& other);
			vec4& divide(const vec4& other);

			friend vec4 operator+(vec4 left, const vec4& right);
			friend vec4 operator-(vec4 left, const vec4& right);
			friend vec4 operator*(vec4 left, const vec4& right);
			friend vec4 operator/(vec4 left, const vec4& right);

			bool operator==(const vec4& other);
			bool operator!=(const vec4& other);

			vec4& operator+=(const vec4& other);
			vec4& operator-=(const vec4& other);
			vec4& operator*=(const vec4& other);
			vec4& operator/=(const vec4& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);

			float magnitude();
			void normalize();
		};
	}
}