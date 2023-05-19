#include "test_scene.h"

#include <iostream>

#include "../animation/node_interpolates.h"

#include "../object_manager/object_player.h"


namespace bk
{

template<typename T>
class test_animation :
    public animation_sine<T>
{
protected:
    void on_state_changed(const animation_state& new_state) override
    {
        if (new_state == animation_state::done && this->get_state() != animation_state::done)
        {
            this->set_next_animation(new test_animation<sf::Vector2<double>>(
                this->m_value, this->get_end_value(), this->get_start_value(), 2.0, 0.0
            ));
        }
    }

public:
    using animation_sine<T>::animation_sine;
};

test_scene::test_scene(const sf::Vector2u& dimensions) :
    scene(dimensions)
{
    /*
    auto* animation = new test_animation<sf::Vector2<double>>(
        &position, sf::Vector2<double>(20, 20), sf::Vector2<double>(50, 50), 2.0, 0.0
    );
    m_system.push_animation(animation);*/

    object_npc *p_obj = m_game_state.m_obj_mgr.create<object_npc>(*this);
}

void test_scene::on_update(double dt) 
{
    m_surface.setView(get_view());
    m_system.update();
}

void test_scene::on_render() 
{
    m_surface.clear();
}

}