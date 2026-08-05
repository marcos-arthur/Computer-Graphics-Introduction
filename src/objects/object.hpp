#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "common.hpp"
#include "canvas.hpp"

namespace pet
{
    enum class DrawMethod{
        Bresenhan = 0,
        BresenhanMidpoint,
    };

    class Object {
        protected:
            Point2 scale;
            double thick;
        
            public:
                Object(Point2 scale = Point2(1,1), double thick = 1) : scale(scale), thick(thick) {};

                virtual ~Object() = default;

                virtual void drawObject(Canvas &canvas, RGBColor color, DrawMethod method = DrawMethod::Bresenhan) = 0;
    };
}

#endif
