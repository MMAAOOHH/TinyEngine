#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include "shader.h"
#include "texture.h"
#include "renderer.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "Window.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "rect.h"

const GLuint SCR_WIDTH  = 800;
const GLuint SCR_HEIGHT = 600;
const char* NAME = "TinyEngine";

void process_input();



Rect dest = { 400 - 32, 300 - 32, 64, 64 };
Rect src = { 0,0,64,64 };


constexpr auto SPEED = 4.0f;

glm::mat4 mouse_transform = glm::mat4(1.0f);


struct Player
{
    Rect rect;
    Component::Material* mat;
};

int main()
{
    Window window(NAME, SCR_WIDTH, SCR_HEIGHT);

	// Load from shader files
	// ----------------------
	auto vs_file_name = "res/Shaders/sprite.vs";
	auto fs_file_name = "res/Shaders/sprite.fs";

    auto shader = Component::Shader();
    shader.load(vs_file_name, fs_file_name);

    // load in texture
    auto tex_file_name = "res/Images/testtexture.png";

    auto texture = Component::Texture();
    texture.load(tex_file_name);

    shader.use();
    // set up 2d camera
    auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    shader.set_mat4("projection", projection);

    // material
    auto material = Component::Material(texture, shader, 0);


    auto* renderer = new Component::Renderer({ 2, 2 }, 255);
    auto* player = new Player();

    player->rect = { SCR_WIDTH / 2 - 32, SCR_HEIGHT / 2 - 32, 64, 64 };
    player->mat = &material;

    // Main loop
    while (window.is_open())
    {
        window.process_events();
        process_input();

        glClearColor(.1f, .1f, .1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw rects
        renderer->draw(player->rect, player->rect, *player->mat);
        renderer->end();
        window.update();
    }
    return 0;
}


void process_input()
{
    if (Keyboard::key(GLFW_KEY_UP))
        dest.y -= SPEED;
    if (Keyboard::key(GLFW_KEY_DOWN))
        dest.y += SPEED;
    if (Keyboard::key(GLFW_KEY_RIGHT))
        dest.x += SPEED;
    if (Keyboard::key(GLFW_KEY_LEFT))
        dest.x -= SPEED;
}