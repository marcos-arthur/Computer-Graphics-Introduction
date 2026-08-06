#include "floodFill.hpp"
#include "common.hpp"
#include <cstdlib>
#include <stack>
namespace pet{
    
    void FloodFill::fill(Canvas& canvas, const Pixel& seed, const RGBColor& fillColor){
      RGBColor original_color;
		  auto original_color_optional = canvas.pixel(seed);
      if(original_color_optional.has_value()){
        original_color = original_color_optional.value();
      } else{
        return;
      }

      if(Fill::colorsMatch(original_color, fillColor)){
        return;
      }

      std::stack<Pixel> visit_stack;
      visit_stack.push(seed);

      while(!visit_stack.empty()){
        Pixel to_visit = visit_stack.top();
        visit_stack.pop();
        canvas.add(to_visit, fillColor);

        auto up_color = canvas.pixel(Pixel{to_visit.x(), to_visit.y()-1});
        if (up_color.has_value() && colorsMatch(original_color, up_color.value())){
          visit_stack.push({to_visit.x(), to_visit.y()-1});
        }

        auto right_color = canvas.pixel(Pixel{to_visit.x()+1, to_visit.y()});
        if (right_color.has_value() && colorsMatch(original_color, right_color.value())){
          visit_stack.push({to_visit.x()+1, to_visit.y()});
        }

        auto down_color = canvas.pixel(Pixel{to_visit.x(), to_visit.y()+1});
        if (down_color.has_value() && colorsMatch(original_color, down_color.value())){
          visit_stack.push({to_visit.x(), to_visit.y()+1});
        }

        
        auto left_color = canvas.pixel(Pixel{to_visit.x()-1, to_visit.y()});
        if (left_color.has_value() && colorsMatch(original_color, left_color.value())){
          visit_stack.push({to_visit.x()-1, to_visit.y()});
        }
      }
    }
    
};
