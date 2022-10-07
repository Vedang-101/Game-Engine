#include "Core/utils/timer.h"
#include "Core/graphics/window.h"
#include "Core/input/desktop.h"

#include "Core/maths/maths.h"

#include "Core/graphics/shader.h"
#include "Core/graphics/camera.h"

#include"Core/graphics/renderables/sprite.h"
#include "Core/graphics/renderables/label.h"
#include "Core/graphics/layers/tilelayer.h"
#include "Core/graphics/layers/group.h"

#include "Core/graphics/textures/spritesheet.h"

#include "Core/animations/spriteanimation.h"

using namespace rse;

int main() {
	{
		//By Default FullScreen (To make it windowed, specify width and height as extra params)
		graphics::Window window("The Other Side: Prologue", 960, 540);
		const int Width = window.getWidth();
		const int Height = window.getHeight();


		//Colours are represented in hexa decimal format in "ARGB" meaning 0xaarrggbb respectively
		window.setBackground(0xffffffff);
		window.setWindowIcon("res/textures/Cancel.png");

		//Creating a Camera will allow the objects to be rendered
		//Projection Matrix is set to orthographic because of being a 2D engine
		graphics::Camera mainCamera(Width, Height);
		float ProjectionWidth = 472;
		float ProjectionHeight = 265;

		mainCamera.setProjectionMatrix(0.0f, ProjectionWidth, 0.0f, ProjectionHeight, -1.0f, 1.0f);

		graphics::Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");

		//Create Layers in the sorting order you wish to render them
		graphics::TileLayer layer(&mainCamera, &shader);

		//graphics::FontManager::add(new graphics::Font("shanders", "res/fonts/agencyr.ttf", 72));
		//graphics::SpriteSheet spriteSheet("res/textures/isometric.png", 7, 8);

		graphics::Texture sky_texture("res/textures/sky.png");
		graphics::Texture ocean_texture("res/textures/ocean.png");
		graphics::Texture ship_texture("res/textures/ship.png");

		//graphics::Sprite *player = new graphics::Sprite(maths::vec2(8, 4.5f), maths::vec2(1.5f, 1.5f), 0, &spriteSheet, 0);

		graphics::Group *sky_background = new graphics::Group(maths::mat4::translation(maths::vec3(0,0,-2.0f)));
		unsigned int sky = sky_background->add(new graphics::Sprite(maths::vec2(0, 0), maths::vec2(ProjectionWidth, ProjectionHeight), 0, &sky_texture));
		graphics::Sprite *ship = new graphics::Sprite(maths::vec2(145/2, 73), maths::vec2(145, 73), 0, &ship_texture);
		sky_background->add(ship);

		graphics::Group *ocean_foreground = new graphics::Group(maths::mat4::translation(maths::vec3(0, 0, 0.0f)));
		unsigned int ocean = ocean_foreground->add(new graphics::Sprite(maths::vec2(0, -63), maths::vec2(ProjectionWidth, 137), 0, &ocean_texture));

		layer.add(sky_background);

		layer.add(ocean_foreground);

		//unsigned int sprite1ID = layer1.add(player);
		//unsigned int Text1ID = layer.add(new graphics::Label("The quick brown fox, jumped over the lazy fox!", 0.5f, 0.5f, "shanders", 1, 0xff000000));

		utils::Timer time;

		//Animations: (SpriteAnimation), PositionAnimation, ScaleAnimation, RotationAnimation, ColorAnimation

		/*animation::SpriteAnimation *animations[] = {
			new animation::SpriteAnimation(15.0f, player),
			new animation::SpriteAnimation(15.0f, player),
			new animation::SpriteAnimation(15.0f, player),
			new animation::SpriteAnimation(15.0f, player),
			new animation::SpriteAnimation(15.0f, player),
			new animation::SpriteAnimation(15.0f, player),
			new animation::SpriteAnimation(15.0f, player),
			new animation::SpriteAnimation(15.0f, player),
			new animation::SpriteAnimation(15.0f, player)
		};

		animations[0]->addKeyframes(0, 8);
		animations[1]->addKeyframes(8, 14);
		animations[2]->addKeyframes(14, 20);
		animations[3]->addKeyframes(20, 26);
		animations[4]->addKeyframes(26, 32);
		animations[5]->addKeyframes(32, 38);
		animations[6]->addKeyframes(38, 44);
		animations[7]->addKeyframes(44, 49);
		animations[8]->addKeyframes(49, 56);*/
		float deltaTime = 0;
		float lastFrameTime = time.elapsed();

		float x = 50;
		float speed = 15.0f;

		while (!window.closed()) {
			deltaTime = time.elapsed() - lastFrameTime;
			lastFrameTime = time.elapsed();

			window.clear();

			if (input::Desktop::isKeyTyped(GLFW_KEY_ESCAPE))
				window.close();
			
			//Update sprites
/*			if (input::Desktop::isKeyPressed(GLFW_KEY_LEFT)) {
				x -= deltaTime * speed;
				ship->setScale({ 1, 1 });
				ship->setTransition({ x, 5 });
			} else if (input::Desktop::isKeyPressed(GLFW_KEY_RIGHT)) {
				x += deltaTime * speed;
				ship->setScale({ -1, 1 });
				ship->setTransition({ x, 5 });
			}
*/
			layer.render();
			//End of Update Sprites

			window.update();
		}
	}
	#ifdef ENGINE_DEBUG
	system("PAUSE");
	#endif
	return 0;
}