#ifndef LINE_HPP
#define LINE_HPP

#include "common.hpp"
#include "canvas.hpp"
#include "object.hpp"

namespace pet
{
    class Line : public Object{
        private:
            Point2 start;
            Point2 end;
        
        public:
            Line(Point2 start, Point2 end, Point2 scale = Point2(1,1), double thick = 1):
            Object(scale, thick), start(start), end(end) {};

            void drawObject(Canvas &canvas, RGBColor color, DrawMethod method = DrawMethod::Bresenhan) override;
    };
}

#endif
