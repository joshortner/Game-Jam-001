#include "bullet_killer.h"

#include "SFML/Window.hpp"

#include <stdio.h>

int main() {
    printf("TEST: %s\n", bk::get_asset_dir());

    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    // Create the main window
    sf::Window window(sf::VideoMode({ 640, 480 }), "SFML window with OpenGL", sf::Style::Default, contextSettings);
}