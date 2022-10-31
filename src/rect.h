#pragma once
#include <glad/glad.h>
#include "glm/gtc/matrix_transform.hpp"


struct rect
{
    GLfloat x, y, w, h;
};

struct drawable
{
    enum type
    {
	    quad,
        circle,
        line
    };

    type type = quad;

    glm::vec2 position = glm::vec2(0.0f);
    GLfloat rotation = 0.0f;
    glm::vec2 size = glm::vec2(64.0f);
    Component::Material* material;

    glm::mat4 get_model_transform()
    {
        glm::mat4 model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::rotate(model, -rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(size, 1.0f));

        return model;
    }
};