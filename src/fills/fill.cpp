#include "fill.hpp"

namespace pet 
{
  bool Fill::colorsMatch(const RGBColor& color1, const RGBColor& color2, double tolerance) const {
    double R_diff = abs(color1.red - color2.red);
    double G_diff = abs(color1.green - color2.green);
    double B_diff = abs(color1.blue - color2.blue);

    if(R_diff > tolerance || G_diff > tolerance || B_diff > tolerance) return false;

    return true;
  };
}
