#include "application.h"
#include "main_menu_scene.h"
#include "scene/test_scene.h"

/*
Main character: Cowboy Synth
*/

int main()
{
    //bk::test_scene* scene = new bk::test_scene({ 640, 360 });
    bk::main_menu_scene* scene = new bk::main_menu_scene({ 640, 360 });
    bk::application& application = bk::application::create({ 1280, 720 }, scene);
    application.run();
    bk::application::destroy();
}
