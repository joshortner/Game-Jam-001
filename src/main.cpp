#include "bullet_killer.h"

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include <stdio.h>

class test_scene : 
    public bk::scene
{
public:
    using bk::scene::scene;

    void on_update(double dt) override
    {

    }

    void on_render() override
    {

    }
};

int main()
{
    test_scene scene({ 120, 120 });
    bk::application application({ 800, 600 }, &scene);
    application.run();
}

int main2() {
    printf("TEST: %s\n", bk::get_asset_dir());

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