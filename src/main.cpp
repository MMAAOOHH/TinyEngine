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


rect dest = { 400 - 32, 300 - 32, 64, 64 };
rect src = { 0,0,64,64 };

constexpr auto SPEED = 4.0f;
glm::mat4 mouse_transform = glm::mat4(1.0f);


struct drawable
{
    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 size = glm::vec2(100.0f);
    glm::vec3 color = glm::vec3(1.0f);
    float rotation = 0.0f;

    Component::Material* material;
};

int main()
{
    Window window(NAME, SCR_WIDTH, SCR_HEIGHT);

	auto vs_file_name = "res/Shaders/sprite.vs";
	auto fs_file_name = "res/Shaders/sprite.fs";

    auto shader = Component::Shader();
    shader.load(vs_file_name, fs_file_name);

    // load in texture
    auto tex_file_name = "res/Images/white.png";

    auto texture = Component::Texture();
    texture.load(tex_file_name);

    shader.use();
    // set up 2d camera
    auto projection = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    shader.set_mat4("projection", projection);

    // create renderer and material
    auto material = Component::Material(texture, shader, 0);
    auto renderer = Component::Renderer({ 2, 2 }, 255);

    while (window.is_open())
    {
        window.process_events();
        window.clear();

        dest.y = Mouse::get_mouse_y() - 32;
        dest.x = Mouse::get_mouse_x() - 32;

        renderer.draw(dest, src, material);
        renderer.end();
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