#include "application.h"
#include "../scene/scene.h"

namespace bk
{
    application::application(const sf::Vector2u& dimensions, scene* const start_scene) :
        mwindow(sf::VideoMode(dimensions), "whats up"),
        mscenes({ start_scene })
    {

    }

    void application::run()
    {
        while (mwindow.isOpen() && mscenes.size())
        {
            sf::Event event;
            while (mwindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    mwindow.close();
            }

            mwindow.clear();

            scene* current_scene = mscenes.back();
            if (current_scene->get_state() == scene_state::complete)
            {
                delete current_scene;
                mscenes.pop_back();
                current_scene = mscenes.back();
            }

            current_scene->on_update(0.0);
            current_scene->on_render();

            sf::Sprite surface(mscenes[mscenes.size() - 1]->get_texture());
            mwindow.draw(surface);

            mwindow.display();
        }
    }
}