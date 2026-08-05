#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "common.hpp"
#include "canvas.hpp"
#include "object.hpp"

namespace pet
{
    class Circle : public Object{
        protected:
            double radius;
            Point2 center;

        public:
            Circle(double radius, Point2 center, Point2 scale = Point2(1,1), double thick = 1):
            Object(scale, thick), radius(radius), center(center) {};

            void drawObject(Canvas& canvas, RGBColor color, DrawMethod method = DrawMethod::Bresenhan) override;
    };
}

#endif
