#pragma once

#include "../scene/scene.h"
#include "../object_bullet.h"

namespace bk
{
    class object_exploder_bullet :
        public object_bullet
    {
    public:
        using object_bullet::object_bullet;

        void on_update(double dt) override
        {
            m_pos += (float)dt * 250.f * m_direction;

            if (clock.getElapsedTime().asSeconds() > 0.6 && !m_done)
            {
                const int   segments = 20;
                const float TWO_PI = 2.f * 3.14159f;
                const float dtheta = TWO_PI / (float)segments;

                for (float theta = 0.f; theta <= TWO_PI; theta += dtheta)
                {
                    const sf::Vector2f dir = sf::Vector2f(
                        cos(theta), sin(theta)
                    );

                    m_scene.get_game_state().m_obj_mgr.create<object_bullet>(
                        m_scene, get_pos(), dir, m_texture, 0.1
                    );
                }

                set_done(true);
            }
        }

    private:
        sf::Clock clock;
    };
}