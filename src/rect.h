#pragma once
#include <glad/glad.h>

struct rect
{
    GLfloat x, y, w, h;
};

struct drawable
{
    glm::vec2 position = glm::vec2(0.0f);
    GLfloat rotation = 0.0f;
    glm::vec2 size = glm::vec2(64.0f);

    Component::Material* material;
};