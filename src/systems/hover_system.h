#pragma once

namespace bk
{

class scene;

class hover_system
{
public:
    hover_system(scene &s) : m_scene(s) { }
    void on_update(double dt);
private:
    scene& m_scene;
};

}