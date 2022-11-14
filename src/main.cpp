#include <glad/glad.h>
#include "Engine.h"

const GLuint SCR_WIDTH  = 1080;
const GLuint SCR_HEIGHT = 1080;

int main()
{
    Prototype game(SCR_WIDTH, SCR_HEIGHT);
    game.start();
    game.run();
    return 0;
}


/*
Window window(NAME, SCR_WIDTH, SCR_HEIGHT);
Camera camera;
camera.view_size = { SCR_WIDTH , SCR_HEIGHT };

// Shaders
auto vs_file_name = "res/Shaders/sprite.vs";
auto quad_fs_file_name = "res/Shaders/sprite.fs";
auto circ_fs_file_name = "res/Shaders/circle.fs";

auto quad_shader = Shader();
quad_shader.load(vs_file_name, quad_fs_file_name);

auto circ_shader = Shader();
circ_shader.load(vs_file_name, circ_fs_file_name);

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
Material circ_mat(texture, circ_shader, 0);
Material quad_mat(texture, quad_shader, 0);

quad_mat.color = { 0.0,1,0.4 };
circ_mat.color = quad_mat.color;

// create renderer
auto renderer = new SpriteRenderer();

//drawable test
std::vector<drawable*> drawables;
drawable a, b;

a.camera = &camera;
a.material = &circ_mat;
b.material = a.material;
b.camera = a.camera;

a.size = glm::vec2(40);
b.size = a.size;

// line segment
auto c = line(a.position, b.position);
c.camera = a.camera;
c.material = &quad_mat;

drawables.push_back(&a);
drawables.push_back(&b);
drawables.push_back(&c);

b.position.x = a.position.x + 400;

*/


