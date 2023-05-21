#include "object_person.h"
#include "object_player.h"

#include "../scene/scene.h"

namespace bk
{
    object_person::object_person(scene& scene, const sf::Texture& texture) :
        object_itf(scene, object_type::person),
        m_sprite(texture)
    {   
        m_position.x = (rand() % 1000) / 1000.f * 640;
        m_position.y = (rand() % 1000) / 1000.f * 360;
        m_random_offset = (rand() % 1000) / 1000.f * 10.f;
    }

    void object_person::on_update(double dt) 
    {
        // choose a frame
        int32_t frame = ((int)((clock.getElapsedTime().asSeconds() + m_random_offset) * 2.0)) % 2;
        m_sprite.setTextureRect(sf::IntRect(
            { frame * 16, 0 },
            { 16, 16 }
        ));

        // time to move
        sf::Vector2f dir = { 0, 0 };

        std::vector<object_person*> people;
        m_scene.get_game_state().m_obj_mgr.get_object_type(people);
        for (auto* person : people)
        {
            if (person == this) continue;

            const sf::Vector2f displacement = person->m_position - m_position;
            dir = dir - displacement.normalized() * 550.f / powf(displacement.length(), 2) / ((m_random_offset + 1.f) / 8.f);
        }

        const sf::Vector2f target = sf::Vector2f(640 / 2, 360 / 2);
        dir += (target - m_position);
        dir -= (target - m_position) * 200.f / (target - m_position).length();

        dir -= sf::Vector2f(0, m_position.y) * 0.5f;
        dir -= sf::Vector2f(0, m_position.y - m_scene.get_size().y) * 0.5f;

        dir -= sf::Vector2f(m_position.x, 0) * 0.1f;
        dir -= sf::Vector2f(m_position.x - m_scene.get_size().x, 0) * 0.1f;

        /*
        std::vector<object_player*> player;
        m_scene.get_game_state().m_obj_mgr.get_object_type(player);
        dir += (m_position - player[0]->get_pos()).normalized() * 10000.f / powf((m_position - player[0]->get_pos()).length(), 4);*/
        
        const float K = 0.5f;
        const float m = 1.f;
        sf::Vector2f a = (dir - 3.f * K * m_velocity) / m;
        m_velocity += a * (float)dt;
        m_position += m_velocity * (float)dt;

        m_sprite.setPosition(m_position);
    }

    void object_person::on_render(sf::RenderTarget& target) 
    {
        target.draw(m_sprite);
    }

    void object_person::on_event(event e) 
    {

    }
}