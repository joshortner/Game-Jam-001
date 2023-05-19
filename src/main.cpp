#include "bullet_killer.h"
#include "object_mgr.h"

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include <stdio.h>

class test_scene : 
    public bk::scene
{
    float x = 0;
    float y = 0;

public:
    using bk::scene::scene;

    void on_update(double dt) override
    {
        static double t = 0;
        t += dt;

        y = (1 + sin(t)) * 220.f;
        x = (1 + cos(t)) * 220.f;
    }

    void on_render() override
    {
        m_surface.clear();

        sf::RectangleShape rect;
        rect.setPosition({x, y});
        rect.setSize(sf::Vector2f(20, 20));
        rect.setFillColor(sf::Color::Red);
        m_surface.draw(rect);

        m_surface.display();
    }
};

int main()
{
    test_scene scene({ 640, 480 });
    bk::application application({ 1280, 720 }, &scene);
    application.run();
}

int main2() {
    printf("TEST: %s\n", bk::get_asset_dir());

    bk::object_mgr obj_mgr;
    bk::object_handle obj = obj_mgr.create_npc();

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        
        // Update the window
        window.display();
    }
   
    return EXIT_SUCCESS;
}