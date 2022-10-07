#pragma once

#include "virtualanimation.h"
#include "../graphics/renderables/rendererable2d.h"

namespace rse {
	namespace animation {
		class SpriteAnimation : public Animation {
		private:
			std::vector<int> m_sprites;
			graphics::Renderable2D* m_Renderable;
			int m_current;
		public:
			SpriteAnimation(float FrameRate, graphics::Renderable2D* sprite)
				: m_current(0), m_Renderable(sprite)
			{
				m_speed = 1.0f / FrameRate;
				m_time = 0;
				m_playing = false;
			}

			void addKeyframes(std::list<int> keyframes) {
				std::list <int> ::iterator it;
				for (it = keyframes.begin(); it != keyframes.end(); it++)
					m_sprites.push_back(*it);
			}

			void addKeyframes(int start, int end) {
				for (int i = start; i < end; i++)
					m_sprites.push_back(i);
			}

			void Start() override {
				m_playing = true;
				m_time = 0;
				m_current = 0;
			};

			void Stop() override {
				m_playing = false;
				m_time = 0;
				m_current = 0;
			};

			void Update(float deltaTime) override {
				if (m_playing) {
					m_time += deltaTime;
					if (m_time > m_speed) {
						m_current = (m_current + 1) % m_sprites.size();
						m_time = 0;
					}
					m_Renderable->setSprite(m_sprites[m_current]);
				}
			}
		};
	}
}