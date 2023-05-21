#include "object_enemy.h"
#include "../scene/scene.h"
#include "object_bullet.h"

namespace bk
{
    object_enemy::object_enemy(scene& scene, object_player* player, const sf::Vector2f& pos) :
        object_itf(scene, object_type::enemy),
        m_player(player)
    {
        m_rect.setSize({ 16.f, 16.f });
        m_rect.setFillColor(sf::Color::Blue);
        m_rect.setPosition(pos);

        random_t_offset = (rand() % 1000) / 1000.f * 2.f;
    }

    void object_enemy::on_update(double dt) 
    {
        static double t = 0;
        t += dt;
        hp_offset = sin(0.5f * (random_t_offset + t));

        // check all bullet collisions
        std::vector<object_bullet*> bullets;
        m_scene.get_game_state().m_obj_mgr.get_object_type(bullets);

        for (auto* bullet : bullets)
        {
            if (m_rect.getGlobalBounds().contains(bullet->get_pos()))
            {
                //m_scene.get_game_state().m_obj_mgr.remove_object(bullet);
                bullet->set_done(true);
                hp -= 0.1f;
            }
        }

        // movement towards player
        const sf::Vector2f dir = (m_player->get_pos() - m_rect.getPosition()).normalized();
        const float movement_speed = 20.f;
        m_rect.move(movement_speed * dir * (float)dt);
    }

    void object_enemy::on_render(sf::RenderTarget& target) 
    {
        target.draw(m_rect);

        sf::RectangleShape health;
        health.setSize(sf::Vector2f(16.f, 4.f));
        health.setFillColor(sf::Color::Red);
        health.setPosition(m_rect.getPosition());
        health.setOutlineThickness(1.f);
        health.setOutlineColor(sf::Color::Black);
        health.move(sf::Vector2f(0, -7 + hp_offset));
        target.draw(health);

        health.setOutlineThickness(0.f);
        health.setScale(sf::Vector2f(hp, 1));
        health.setFillColor(sf::Color::Green);
        target.draw(health);
    }

    void object_enemy::on_event(event e) 
    {

    }
}