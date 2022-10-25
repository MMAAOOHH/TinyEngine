#include"Window.h"
#include "Mouse.h"
#include "Keyboard.h"


void process_input(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


Window::Window(const char* name, GLuint width, GLuint height)
	: name_(name), width_(width), height_(height)
{
	init(name_, width_, height_);
}

Window::~Window()
{
	glfwDestroyWindow(window_);
	glfwTerminate();
}

void Window::init(const char* name, GLuint width, GLuint height)
{
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(width, height, name, NULL, NULL);

	// Create OpenGL Context
	glfwMakeContextCurrent(window_);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(2);

	// normalize window to work on other devices
	glViewport(0, 0, 800, 600);

	// Configure OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//glEnable(GL_DEPTH_TEST); Hides my sprite, why?

	// set up alpha channel to display images beneath it.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Bind input callbacks
	glfwSetKeyCallback(window_, Keyboard::key_callback);
	glfwSetCursorPosCallback(window_, Mouse::cursor_pos_callback);
	glfwSetScrollCallback(window_, Mouse::mouse_wheel_callback);

	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
}

void Window::process_events()
{
	glfwPollEvents();

	if (Keyboard::key(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window_, GL_TRUE);
}

void Window::update()
{
	glfwSwapBuffers(window_);
}

bool Window::is_open()
{
	 return (!glfwWindowShouldClose(window_));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}