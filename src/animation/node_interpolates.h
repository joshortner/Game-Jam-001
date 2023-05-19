#pragma once

#include "node_type.h"

namespace bk
{
    template<typename T>
    class animation_sine :
        public animation<T>
    {
    public:
        using animation<T>::animation;
        ~animation_sine() = default;

        double interpolate(const double& t) const override;
    };

    template<typename T>
    double animation_sine<T>::interpolate(const double& t) const
    {
        //double a = -1.0 / (2.0 * 0.8 - 1.0);
        //double coeff = a * t * t + (1 - a) * t;

        return 1.0 * sin(t * 3.14159 / 2.0);
    }
}