#include "Engine.h"
#include "Mouse.h"


Engine::Engine(GLuint width, GLuint height)
	: width(width), height(height)
{
};

Engine::~Engine()
{
	/*
	delete &renderer;
	delete &camera;
	delete &quad_mat;
	delete &circ_mat;
	delete &window;
	*/
}

void Engine::init()
{
	window = std::make_unique<Window>("TinyEngine", width, height);
	renderer = std::make_unique<SpriteRenderer>();
	camera = std::make_unique<Camera>();

	// Shaders
	auto vs_file_name = "res/Shaders/sprite.vs";
	auto quad_fs_file_name = "res/Shaders/sprite.fs";
	auto circ_fs_file_name = "res/Shaders/circle.fs";

	quad_shader = new Shader();
	quad_shader->load(vs_file_name, quad_fs_file_name);

	circ_shader = new Shader();
	circ_shader->load(vs_file_name, circ_fs_file_name);

	
	auto projection = camera->get_orthographic_projection();

	quad_shader->use();
	quad_shader->set_mat4("u_projection", projection);

	circ_shader->use();
	circ_shader->set_mat4("u_projection", projection);

	// Texture
	auto tex_file_name = "res/Images/white.png";
	texture = new Texture();
	texture->load(tex_file_name);

	// Materials
	quad_mat = new Material(texture, quad_shader, 0);
	circ_mat = new Material(texture, circ_shader, 0);

}


void Engine::handle_input()
{
	window->process_events();
}

double old_time = 0;
void Engine::update()
{
	// delta time
	double time = glfwGetTime();
	delta_time = static_cast<GLfloat>(time - old_time);
	old_time = time;

	// update camera
	// Zoom
	camera->zoom = lerp(camera->zoom, camera->zoom + static_cast<GLfloat>(Mouse::get_scroll_dy()), camera->zoom_sensitivity * delta_time);
	//  Pan
	if (Mouse::button(1))
		camera->position += glm::vec2(Mouse::get_mouse_dx(), Mouse::get_mouse_dy());

	// Update objects
	for (auto& entry : objects)
		entry->update(delta_time);
}

void Engine::render()
{
	window->clear();

	for (auto& game_object : objects)
		game_object->draw(*renderer, camera->transform_view());

	window->update();
}

void Engine::add_game_object(const std::shared_ptr<GameObject>& go)
{
	objects.push_back(go);
	go->start();
}

void Engine::remove_game_object(const std::shared_ptr<GameObject>& go)
{
	// Todo: move to back and pop from list ?
}
