#include "application.h"
#include "main_menu_scene.h"

/*
Main character: Cowboy Synth
*/

int main()
{
    bk::main_menu_scene scene({ 640, 360 });
    bk::application& application = bk::application::create({ 1280, 720 }, &scene);
    application.run();
}
