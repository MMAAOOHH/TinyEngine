#pragma once

#include "game_object.h"
#include "Window.h"
#include "renderer.h"

struct Engine
{
	Engine(GLuint width, GLuint height);
	~Engine();
	GLuint width, height;

	std::unique_ptr<Window> window;
	std::unique_ptr <SpriteRenderer> renderer;
	std::unique_ptr <Camera> camera;

	//unique ptr, shared ptr
	// array of shaders, array of textures
	Shader* quad_shader;
	Shader* circ_shader;
	Material* quad_mat;
	Material* circ_mat;
	Texture* texture;

	GLfloat delta_time;

	void init();
	void start();
	void handle_input();
	void update();
	void render();

	std::vector<std::shared_ptr<GameObject>> objects;
	void add_game_object(const std::shared_ptr<GameObject>& go);
	void remove_game_object(const std::shared_ptr<GameObject>& go);
};

struct Game
{
	Game() = default;
	virtual ~Game() = default;

	virtual void run() = 0; // while loop
	virtual void start() = 0;
	virtual void update(GLfloat dt) = 0;
};

struct Prototype : Game
{
	std::unique_ptr<Engine> engine;

	Prototype(GLuint width, GLuint height)
	{
		engine = std::make_unique<Engine>(width, height);
		engine->init();
	}
	~Prototype() override = default;

	void run() override
	{
		while (engine->window->is_open())
		{
			engine->handle_input();
			engine->update();
			engine->render();
		}
	}
	void start() override
	{
		auto a = std::make_shared<GameObject>();
		auto drawable = std::make_shared<struct drawable>();
		drawable->material = engine->circ_mat;

		a->drawables.push_back(drawable);

		engine->add_game_object(a);
	}
	void update(GLfloat dt) override
	{
		
	}
};
