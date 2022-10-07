#pragma once

#include <vector>

namespace rse {
	namespace animation {
		class Animation {
		protected:
			float m_speed;
			float m_time;
			bool m_playing;
		protected:
			Animation() {};
		public:
			virtual void Start() { m_playing = true; m_time = 0; };
			virtual void Update(float deltaTime) {};
			virtual void TogglePause() { m_playing = !m_playing; };
			virtual void Stop() { m_playing = false; m_time = 0; };
		};
	}
}