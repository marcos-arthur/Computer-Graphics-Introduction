#include "medianFilter.hpp"
#include "canvas.hpp"
#include "common.hpp"

namespace pet {

    RGBColor MedianFilter::filterFunction(Pixel& p, Canvas& canvas){
		  int pad = kernel_size/2;
      int x = p.x();
      int y = p.y();
      int width = canvas.width();
      int height = canvas.height();

      const vector<RGBColor> & data = canvas.data();
      vector<double> _red, _green, _blue;

      for (int i = -pad; i <= pad; i++){
        for (int j = -pad; j < pad; j++){
            if (x+i >= width || x+i < 0 || y + j >= height || y + j < 0){
              continue;
            }
            _red.push_back(data[(y+j) * width + i + x].red);
            _green.push_back(data[(y+j) * width + i + x].green);
            _blue.push_back(data[(y+j) * width + i + x].blue);
        }
      }

      std::sort(_red.begin(), _red.end());
      std::sort(_green.begin(), _green.end());
      std::sort(_blue.begin(), _blue.end());

      double r,g,b;
      r = _red.at(_red.size()/2);
      g = _green.at(_green.size()/2);
      b = _blue.at(_blue.size()/2);

      return RGBColor(r,g,b);
    }
};
