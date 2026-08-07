#include "filter.hpp"
#include "common.hpp"


namespace pet {

    void Filter::applyFilter(Canvas& canvas){
		  Canvas temp = canvas;

      for (int i = 0; i < canvas.height(); i++)
      {
        for (int j = 0; j < canvas.width(); j++)
        {
          Pixel p(j,i);
          RGBColor color = filterFunction(p, temp);
          canvas.add(p, color);
        }
      } 
    }
};
