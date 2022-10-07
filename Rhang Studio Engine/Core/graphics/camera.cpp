#include "camera.h"

namespace rse {
	namespace graphics {
		Camera::Camera(int width, int height)
			: m_Width(width), m_Height(height), m_Position(maths::vec3(0, 0, 0)), m_Rot(0), m_ProjectionMatrix(maths::mat4(1.0f))
		{
			m_Renderer = new BatchRenderer2D();
			m_ViewMatrix = maths::mat4::transform(m_Position, m_Rot, maths::vec3(1, 1, 1));
		}

		Camera::Camera(int width, int height, maths::vec3 pos, float rotation)
			: m_Width(width), m_Height(height), m_Position(pos), m_Rot(rotation), m_ProjectionMatrix(maths::mat4(1.0f))
		{
			m_Renderer = new BatchRenderer2D();
			m_ViewMatrix = maths::mat4::transform(m_Position, m_Rot, maths::vec3(1, 1, 1));
		}

		Camera::~Camera() {
			delete m_Renderer;
		}
	}
}