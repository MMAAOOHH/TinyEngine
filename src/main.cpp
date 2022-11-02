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

const GLuint SCR_WIDTH  = 1080;
const GLuint SCR_HEIGHT = 1080;
const char* NAME = "TinyEngine";

glm::vec2 lerp(glm::vec2 a, glm::vec2 b, GLfloat t)
{
    return a + t * (b - a);
}

GLfloat lerp(GLfloat a, GLfloat b, GLfloat t)
{
    return a + t * (b - a);
}



int main()
{
    Window window(NAME, SCR_WIDTH, SCR_HEIGHT);
	camera camera;
    camera.view_size = { SCR_WIDTH , SCR_HEIGHT };
    

	auto vs_file_name = "res/Shaders/sprite.vs";
	auto fs_file_name = "res/Shaders/ghost.fs";

    auto shader = Shader();
    shader.load(vs_file_name, fs_file_name);

    // load in texture
    auto tex_file_name = "res/Images/white.png";

    auto texture = Texture();
    texture.load(tex_file_name);

    shader.use(); //

    auto projection = camera.get_orthographic_projection();
    //auto projection = glm::ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, -1.0f, 1.0f);
    shader.set_mat4("u_projection", projection);
    shader.set_vec2f("u_screenResolution", SCR_WIDTH, SCR_HEIGHT);

    // create renderer
    auto renderer = new SpriteRenderer();
    // create material
    Material material(texture, shader, 0);
    material.color = { 0.9,1,0.4 };


    //drawable test
    std::vector<drawable*> drawables;
    drawable a, b, c;
    drawables.push_back(&a);
    //drawables.push_back(&b);
    //drawables.push_back(&c);

    a.camera = &camera;

    a.material = &material;

    b.material = a.material;
    c.material = a.material;

    a.size = glm::vec2(400 , 400);
    b.size = glm::vec2(30);
    c.size = glm::vec2(50);

    GLfloat old_time = 0;
    GLfloat speed = 2.f;

    a.position = { 0, 0 };

    while (window.is_open())
    {
    	window.process_events();
        window.clear();

    	GLfloat time = glfwGetTime();
        GLfloat delta_time = time - old_time;
        old_time = time;



        // Camera transform
    	camera.zoom = lerp(camera.zoom, camera.zoom + static_cast<GLfloat>(Mouse::get_scroll_dy()), camera.zoom_sensitivity * delta_time);
        if(Mouse::button(1))
            camera.position += glm::vec2(Mouse::get_mouse_dx(), Mouse::get_mouse_dy());

        material.shader.set_float("u_time", time);
        material.shader.set_vec2f("u_mousePos", { Mouse::get_mouse_x(), Mouse::get_mouse_y()});

        // draw
    	for (auto& entry : drawables)
            renderer->draw(*entry);

    	//renderer.end();
        window.update();
    }

    return 0;
}
