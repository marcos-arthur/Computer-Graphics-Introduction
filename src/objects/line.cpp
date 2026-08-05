#include "line.hpp"
#include <cmath>

namespace pet
{
    void Line::drawObject(Canvas &canvas, RGBColor color, DrawMethod method) {
        int x = start.x();
        int y = start.y();

        int dx = end.x() - start.x();
        int dy = end.y() - start.y();

        int stepX = dx >= 0 ? 1 : -1;
        int stepY = dy >= 0 ? 1 : -1;
        
        switch (method) {
            case DrawMethod::Bresenhan: {
                dx = abs(dx);
                dy = - abs(dy);

                
                canvas.add(Pixel(x, y), color);
                int d = dx + dy;

                while(x != end.x() || y != end.y()){
                    int d2 = 2*d;

                    if (d2 >= dy){
                        x += stepX;
                        d += dy;
                    }

                    if (d2 <= dx){
                        y += stepY;
                        d += dx;
                    }

                    
                    canvas.add(Pixel(x, y), color);
                }
                break;
            };

            case DrawMethod::BresenhanMidpoint: {
                dx = abs(dx);
                dy = abs(dy);

                canvas.add(Pixel(x,y), color);

                if(dy <= dx){
                    int d = 2 * dy - dx;
                    int stepE = 2*dy;
                    int stepNE = 2*(dy-dx);

                    while(x != end.x()){
                        x += stepX;

                        if(d < 0){
                            d += stepE;
                        }else{
                            y += stepY;
                            d += stepNE;
                        }

                        canvas.add(Pixel(x,y), color);
                    }
                } else{
                    int d = 2 * dx - dy;
                    int stepN = 2 * dx;
                    int stepNE = 2 * (dx - dy);

                    while(y != end.y()){
                        y += stepY;

                        if (d < 0){
                            d += stepN;
                        }else{
                            x += stepY;
                            d += stepNE;
                        }

                        canvas.add(Pixel(x,y), color);
                    }
                }
            }

        }
    }
}
