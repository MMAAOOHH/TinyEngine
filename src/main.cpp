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


    // Shaders
	auto vs_file_name = "res/Shaders/sprite.vs";
	auto fs_file_name = "res/Shaders/sprite.fs";

    auto quad_shader = Shader();
    quad_shader.load(vs_file_name, fs_file_name);

    auto circ_shader = Shader();
    fs_file_name = "res/Shaders/circle.fs";
    circ_shader.load(vs_file_name, fs_file_name);

    auto projection = camera.get_orthographic_projection();
    quad_shader.use(); //
    quad_shader.set_mat4("u_projection", projection);

    circ_shader.use();
    circ_shader.set_mat4("u_projection", projection);

    // load texture
    auto tex_file_name = "res/Images/white.png";
    auto texture = Texture();
    texture.load(tex_file_name);

   
    // create material
    Material quad_mat(texture, quad_shader, 0);
    Material circ_mat(texture, circ_shader, 0);

    quad_mat.color = { 0.9,1,0.4 };

    // create renderer
    auto renderer = new SpriteRenderer();

    //drawable test
    std::vector<drawable*> drawables;
    drawable a, b;
    
    drawables.push_back(&a);
    drawables.push_back(&b);


    a.camera = &camera;
    a.material = &quad_mat;

    b.material = a.material;
    b.camera = a.camera;

    a.size = glm::vec2(40);
    b.size = a.size;
    

	// line segment
    auto c = line(a.position, b.position);
    c.camera = a.camera;
    c.material = &quad_mat;
   

    drawables.push_back(&c);
    
    /*
    c.transform_origin = drawable::center_left;
    c.position = a.position; // start
    c.size = b.position - a.position; // end
    c.size.y = 1; // thickness
    */

    GLfloat old_time = 0;
    while (window.is_open())
    {
    	window.process_events(); // handle input here aswell?
        window.clear();

        // Move somewhere, Time blabla
    	GLfloat time = glfwGetTime();
        GLfloat delta_time = time - old_time;
        old_time = time;


        // Camera transform
    	camera.zoom = lerp(camera.zoom, camera.zoom + static_cast<GLfloat>(Mouse::get_scroll_dy()), camera.zoom_sensitivity * delta_time);
        if(Mouse::button(1))
            camera.position += glm::vec2(Mouse::get_mouse_dx(), Mouse::get_mouse_dy());

        quad_mat.shader.set_float("u_time", time);
        quad_mat.shader.set_vec2f("u_mousePos", { Mouse::get_mouse_x(), Mouse::get_mouse_y()});


        if (Mouse::button(0))
        {
            
            glm::vec2 mouse_screen_pos = glm::vec2(Mouse::get_mouse_x(), Mouse::get_mouse_y());
            mouse_screen_pos -= (camera.view_size * camera.offset + camera.position) * camera.zoom;
            b.position = mouse_screen_pos;
        }

        c.start = a.position;
        c.end = b.position;
        c.update();


        if (Keyboard::key(GLFW_KEY_SPACE))
        {
			std::cout << "b:" << b.position.x << "," << b.position.y << std::endl;
			std::cout << "m:" << Mouse::get_mouse_x() << "," << Mouse::get_mouse_y() << std::endl;
	        
        }
        

    	// draw
    	//for (auto& entry : drawables)
            renderer->draw(a);
            renderer->draw(b);
            renderer->draw(c);

    	//renderer.end();
        window.update();
    }

    return 0;
}
