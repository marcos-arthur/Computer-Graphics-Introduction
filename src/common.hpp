#ifndef COMMON_HPP
#define COMMON_HPP

#include <ssmath/ssmath.hpp>
#include <array>
#include <cstdio>
#include <optional>
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>

using byte = uint16_t;

using std::cout;
using std::endl;

using std::array;
using std::vector;
using std::string;
using Point3 = vec3<double>;
using Mat2 = mat2<double>;
using Vec3 = vec3<double>;
using Mat3 = mat3<double>;
using Point2 = vec2<int>;
using Pixel = Point2;

// Corner indexes.
enum Corners_e {
  BOTTOM_LEFT = 0,
  TOP_LEFT,
  TOP_RIGHT,
  BOTTOM_RIGHT,
};

namespace pet {

struct RunningOptions {
	std::optional<array<Pixel,2>> crop_region;
	bool quick{false};
	bool verbose{false};
	string outfile = "";
	string scene;
};

struct RGBColor {

  double red;
  double green;
  double blue;

  RGBColor(){
    red = green = blue = .0;
  }

  RGBColor(double _red, double _green, double _blue, std::string type = "RGB"){
    if(type == "RGB"){
      this->red = std::clamp(_red/255.0, 0., 1.);
      this->green = std::clamp(_green/255.0, 0., 1.);
      this->blue = std::clamp(_blue/255.0, 0., 1.);
    }else if(type == "spectre"){
      this->red = std::clamp(_red, 0., 1.); 
      this->green = std::clamp(_green, 0., 1.);
      this->blue = std::clamp(_blue, 0., 1.);
    }
  }

  ~RGBColor() = default;

  RGBColor operator+(const double& c) const {
    return RGBColor( this->red + c, this->green + c, this->blue + c);
  }
  RGBColor operator-(const double& c) const {
    return RGBColor( this->red - c, this->green - c, this->blue - c);
  }
  RGBColor operator*(const double& t) const {
    return RGBColor( this->red * t, this->green * t, this->blue * t);
  }
  RGBColor operator/(const double& t) const {
    return RGBColor( this->red * t, this->green * t, this->blue * t);
  }

  RGBColor operator+(const RGBColor& c) const {
    return RGBColor( this->red + c.red, this->green + c.green, this->blue + c.blue);
  }
  RGBColor operator-(const RGBColor& c) const {
    return RGBColor( this->red - c.red, this->green - c.green, this->blue - c.blue);
  }
  RGBColor operator*(const RGBColor& c) const {
    return RGBColor( this->red * c.red, this->green * c.green, this->blue * c.blue);
  }
  RGBColor operator/(const RGBColor& c) const {
    return RGBColor( this->red / c.red, this->green / c.green, this->blue / c.blue);
  }

  bool operator==(const RGBColor& c) const {
    return this->red != c.red || this->green != c.green || this->blue != c.blue;
  };

  double&    operator[](const size_t index){
    if(index == 0) return this->red;
    if(index == 1) return this->green;
    return this->blue;
  };

};


inline std::istream& operator>>(std::istream& is, pet::RGBColor& color) {
    /*TODO*/
    /*Essa função serve para executar coisas como
      
      cin >> color;
    
    sem precisar preencher cada campo individualmente*/
}
inline std::ostream& operator<<(std::ostream& os, const pet::RGBColor& color) {
    /*TODO*/
    /*Essa função serve para executar coisas como
      
      cout << color;
    
    sem precisar printar cada canal de cor individualmente*/
}

} // namespace rt

#endif //COMMON_HPP
