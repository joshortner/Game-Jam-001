#pragma once

#include "object_itf.h"

namespace bk
{

class object_npc : public object_itf
{
public:

    virtual void on_update() override;   
    virtual void on_render() override;

private:

};

}