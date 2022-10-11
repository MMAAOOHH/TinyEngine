#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include <glm/ext/matrix_clip_space.hpp>

const GLuint SCR_WIDTH  = 800;
const GLuint SCR_HEIGHT = 600;
const char* NAME = "TinyEngine";

void process_input(GLFWwindow* window);
Rect dest = { 400 - 32, 300 - 32, 64, 64 };
Rect src = { 0,0,1,1 };
constexpr auto SPEED = 4.0f;

int main()
{
	if(!glfwInit())
	{
		std::cerr << "Glfw failed to init!" << std::endl;
		return -1;
	}

	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window and get reference
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, NAME, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLAD failed to init!" << std::endl;
		return -1;
	}

    // normalize window to work on other devices
    glViewport(0, 0, 800, 600);

    // set up alpha channel to display images beneath it.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Load from shader files
	// ----------------------
	auto vs_file_name = "res/Shaders/sprite.vs";
	auto fs_file_name = "res/Shaders/sprite.fs";

    auto shader = Shader();
    shader.load(vs_file_name, fs_file_name);

    // load in used textures
    auto tex_file_name = "res/Images/testtexture.png";

    auto texture = Texture();
    texture.load(tex_file_name);

    // use program for drawing
    shader.use();
    // set up 2d camera
    auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    shader.set_mat4("projection", projection);

    // material
    auto material = Material(texture, shader, 0);

    // create a renderer object and input appropriate attribute sizes and max amount of sprites on screen at once
    // 2 = pos, 2 = coords
    auto renderer = Renderer({ 2, 2 }, 255);


    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        // clear screen to red
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw rects
        renderer.draw(dest, src, material);

        // flush draw calls
        renderer.flush();

        glfwSwapBuffers(window);
        glfwPollEvents();

        // exit on escape key press
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        dest.y -= SPEED;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        dest.y += SPEED;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        dest.x += SPEED;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        dest.x -= SPEED;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
