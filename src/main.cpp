#include <ctime>
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <cmath>

#include "shader.h"
#include "texture.h"
#include "renderer.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "Window.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "rect.h"

const GLuint SCR_WIDTH  = 800;
const GLuint SCR_HEIGHT = 800;
const char* NAME = "TinyEngine";

int main()
{
    Window window(NAME, SCR_WIDTH, SCR_HEIGHT);

	auto vs_file_name = "res/Shaders/sprite.vs";
	auto fs_file_name = "res/Shaders/testing.fs";

    auto shader = Component::Shader();
    shader.load(vs_file_name, fs_file_name);

    // load in texture
    auto tex_file_name = "res/Images/white.png";

    auto texture = Component::Texture();
    texture.load(tex_file_name);

    shader.use(); //

    auto projection = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    shader.set_mat4("projection", projection);
    shader.set_vec2f("u_screenResolution", SCR_WIDTH, SCR_HEIGHT);



    // create renderer
	// attribtues { 2, 2 } = vec2 position, vec2 coords
    auto renderer = Component::Renderer({ 2, 2 }, 255);

    // create material
    Component::Material material(texture, shader, 0);
    //material.color = { 0.9,1,0.4 };


    //drawable test
    std::vector<drawable*> drawables;
    drawable a, b, c;
    drawables.push_back(&a);
    //drawables.push_back(&b);
    //drawables.push_back(&c);

    a.material = &material;

    b.material = a.material;
    c.material = a.material;

    a.size = glm::vec2(500);
    b.size = glm::vec2(100);
    c.size = glm::vec2(50);

    GLfloat old_time = 0;
    GLfloat speed = 800.f;
    glm::vec2 direction = { 0.2, 0.5 };


    a.position = { SCR_WIDTH * 0.5 - a.size.x * 0.5, SCR_HEIGHT * 0.5 - a.size.y * 0.5 };
    while (window.is_open())
    {
    	window.process_events();
        window.clear();

    	GLfloat time = glfwGetTime();
        GLfloat delta_time = time - old_time;
        old_time = time;

        shader.set_float("u_time", time);
        shader.set_vec2f("u_mousePos", { Mouse::get_mouse_x(), Mouse::get_mouse_y() });

        /*
        a.position += direction * speed * delta_time;
    	glm::vec2 center = { SCR_WIDTH - a.position.x - a.size.x * 0.5, SCR_HEIGHT - a.position.y - a.size.y * 0.5 };
        if (center.y >= SCR_HEIGHT || center.y <= 0)
            direction.y *= -1;
        if (center.x >= SCR_WIDTH || center.x <= 0)
            direction.x *= -1;
        */
        //b.position = glm::vec2(std::lerp(b.position.x, a.position.x, delta_time * speed), std::lerp(b.position.y, a.position.y, delta_time * speed));
        //c.position = glm::vec2(std::lerp(c.position.x, b.position.x, delta_time * speed * 2), std::lerp(c.position.y, b.position.y, delta_time * speed * 2));

    	for (auto& entry : drawables)
        {
            renderer.draw(*entry);
        }

        renderer.end();
        window.update();
    }
    return 0;
}

rect src = { 0,0,128,128 };
rect dest = { 0,0,0,0 };
constexpr auto SPEED = 4.0f;

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

glm::vec3 random_color()
{
    glm::vec3 col = { rand() & 255, rand() & 255, rand() & 255 };
    return col;
}