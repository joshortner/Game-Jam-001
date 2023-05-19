#include "application.h"
#include "test_scene.h"

/*
Main character: Cowboy Synth
*/

int main()
{
    bk::test_scene scene({ 640, 360 });
    bk::application application({ 1280, 720 }, &scene);
    application.run();
}
