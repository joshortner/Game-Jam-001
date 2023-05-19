#pragma once

#include "scene.h"

namespace bk
{

class test_scene : 
    public bk::scene
{
public:
    using bk::scene::scene;

    void on_update(double dt) override;
    void on_render() override;

private:
    float x = 0;
    float y = 0;
};

}