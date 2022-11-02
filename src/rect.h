#pragma once
#include <glad/glad.h>
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"

struct rect
{
    GLfloat x, y, w, h;
};

struct drawable
{

    enum transform_pivot
    {
	    centered,
    };

    transform_pivot pivot = centered;
    glm::vec2 position = glm::vec2(0.0f);
    GLfloat rotation = 0.0f;
    glm::vec2 size = glm::vec2(64.0f);
    Material* material;
    camera* camera;

    glm::mat4 mat4_translated(glm::mat4 matrix)
    {
        glm::vec2 normal_offset = glm::vec2(0.0f);

        switch (pivot)
        {
        case centered:
            normal_offset.x = 0.5f;
            normal_offset.y = 0.5f;
        }
        return glm::translate(matrix, glm::vec3(-normal_offset * size, 0.0f));
    }

    glm::mat4 get_model_transform()
    {
        glm::mat4 model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        model = mat4_translated(model);
    	model = glm::scale(model, glm::vec3(size, 1.0f));

        return model;
    }
};