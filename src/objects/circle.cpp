#include "circle.hpp"

namespace pet{
        void Circle::drawObject(Canvas& canvas, RGBColor color, DrawMethod) {
        int x = 0;
        int y = radius;
        int d = 1 - radius;

        Pixel p(x,y);
        canvas.add(p, color);
        while (y > x) {
            for (int i{-1}; i <= 1; i += 2) {
                for (int j{-1}; j <= 1; j += 2) {
                    canvas.add(Pixel(center.x() + x * i, center.y() + y * j), color);
                    canvas.add(Pixel(center.x() + y * i, center.y() + x * j), color);
                }
            }
            if (d < 0) {
                d += 2 * x + 1;
                x++;
            }
            else {
                d += -2 * y + 1;
                y--;
            }
        }
    }
}
