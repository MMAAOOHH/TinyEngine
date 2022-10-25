#pragma once
#include <bitset>
#include <glad/glad.h>
#include <glfw3.h>

class Window
{
public:

	Window(const char* name, GLuint width, GLuint height);
	~Window();

	void update();
	void process_events();
	bool is_open();

private:

	void init(const char* name, GLuint width, GLuint height);

	GLFWwindow* window_;
	std::bitset<8> buttons_;

	const char* name_;
	GLuint width_, height_;

};
