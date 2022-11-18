#pragma once

#include "rect.h"
#include "renderer.h"

struct GameObject
{
    std::vector<std::shared_ptr<drawable>> drawables;

    virtual void start(){}
    virtual void update(GLfloat dt)
    {
    }
    virtual void draw(SpriteRenderer& renderer, const glm::mat4& view)
    {
        if (drawables.empty()) return;
        for (auto& drawable : drawables)
            renderer.draw(*drawable, view);
    }
};

/*
struct Circle : GameObject
{
	Circle(Material* circle_mat)
	{
        auto c = std::make_shared<drawable>();
        c->material = circle_mat;
        //c->position
        //this->drawables.push_back(c);
	}
};
struct Plane : GameObject{};
struct Line: GameObject
{
    glm::vec2 start;
	glm::vec2 end;
    GLfloat thickness = 1.f;

    Line(glm::vec2 start, glm::vec2 end)
	    : start(start), end(end)
    {

    }
    void update(GLfloat dt) override
    {
        //for (auto& drawable : drawables)
            //if (auto const l = std::dynamic_pointer_cast<line>(drawable))
                //l->update();
        
    }
};
*/


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



// (gameobject factory)
// be om game object
// singleton - global acces

// engine defaults - default material, default texturer
// 