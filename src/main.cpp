#include "bullet_killer.h"
#include "object_mgr.h"

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include <stdio.h>

int main() {
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