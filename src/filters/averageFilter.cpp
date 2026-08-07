#include "averageFilter.hpp"
#include "canvas.hpp"
#include "common.hpp"

namespace pet {

    RGBColor AverageFilter::filterFunction(Pixel& p, Canvas& canvas){
		  int pad = kernel_size/2;
      int x = p.x();
      int y = p.y();
      int width = canvas.width();
      int height = canvas.height();

      const vector<RGBColor> & data = canvas.data();
      RGBColor sum = RGBColor();
      int pixel_quantity = 0;

      for (int i = -pad; i <= pad; i++){
        for (int j = -pad; j < pad; j++){
            if (x+i >= width || x+i < 0 || y + j >= height || y + j < 0){
              continue;
            }
          pixel_quantity++;
          sum = sum + data[(y+j) * width + i + x];   
        }
      }


      return sum / pixel_quantity;
    }
};
