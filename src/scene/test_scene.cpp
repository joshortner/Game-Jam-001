#include "test_scene.h"

namespace bk
{

void test_scene::on_update(double dt) 
{
    static double t = 0;
    t += dt;

    y = (1 + sin(t)) * 220.f;
    x = (1 + cos(t)) * 220.f;
}

void test_scene::on_render() 
{
    m_surface.clear();

    sf::RectangleShape rect;
    rect.setPosition({x, y});
    rect.setSize(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color::Red);
    m_surface.draw(rect);

    m_surface.display();
}

}