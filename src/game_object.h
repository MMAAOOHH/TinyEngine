#pragma once

#include "Keyboard.h"
#include "rect.h"
#include "renderer.h"

struct GameObject
{
    std::vector<std::shared_ptr<drawable>> drawables;

    virtual void start()
    {
        /*
	    if (!drawables.empty())
		    for (auto& element : drawables)
                element->material->color = { 0,1,0 };
        */
    }
    virtual void update(GLfloat dt){}
    virtual void draw(SpriteRenderer& renderer, const glm::mat4& view)
    {
        if (drawables.empty()) 
            return;

        for (auto& drawable : drawables)
            renderer.draw(*drawable, view);
    }
};

struct Line: GameObject
{
    glm::vec2 start, end;
    GLfloat thickness = 1.f;

    Line()
    {
    	auto line = std::make_shared<struct line>(start, end);
        this->drawables.push_back(line);
    }

};







/*
void update(GLfloat dt) override
{
    for (auto& drawable : drawables)
    {
        // ????????
        static_cast<line&>(*drawable).update(dt);
    }
}
*/