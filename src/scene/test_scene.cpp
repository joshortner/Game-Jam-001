#include "test_scene.h"

namespace bk
{

void test_scene::on_update(double dt) 
{
    static double t = 0;
    t += dt;

    position.x = (1 + cos(t)) * (float)m_surface.getSize().x / 2.f;
    position.y = (1 + sin(t)) * (float)m_surface.getSize().y / 2.f;
}

void test_scene::on_render() 
{
    m_surface.clear();

    sf::RectangleShape rect;
    rect.setPosition(position);
    rect.setSize(sf::Vector2f(20, 20));
    rect.setOrigin({ rect.getSize().x / 2.f, rect.getSize().y / 2.f });
    rect.setFillColor(sf::Color::Red);
    m_surface.draw(rect);

    m_surface.display();
}

}