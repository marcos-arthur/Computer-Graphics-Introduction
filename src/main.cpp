
#include "background.hpp"
#include "interpoledBackground.hpp"
// #include "circle.hpp"
// #include "ellipse.hpp"
#include "common.hpp"
#include "canvas.hpp"
// #include "line.hpp"
// #include "bezier.hpp"
// #include "fills/scanlineFill.hpp"
#include <sys/types.h>


using namespace pet;
const int WIDTH = 40;
const int HEIGHT = 40;

int main() {
    Canvas c(WIDTH, HEIGHT, "teste.ppm", pet::ImgType::PPM3);
    Background b(RGBColor(255,0,255));
    for(int i = 0; i < HEIGHT; i++){
        double u = 0; (double)i/(double)(HEIGHT-1);
        for(int j = 0; j < WIDTH; j++){
            double v = (double)j/(double)(WIDTH-1);
            auto color = b.sample(u,v);
            Pixel pixel(j,i);
            c.add(pixel, color);
        }
    }
    
    c.export_img();
    return 0;
}
