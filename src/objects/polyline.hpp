#ifndef POLYLINE_HPP
#define POLYLINE_HPP

#include "common.hpp"
#include "canvas.hpp"
#include "object.hpp"

namespace pet{
    class Polyline : public Object{
        protected:
            vector<Point2> points;

        public:
            Polyline(vector<Point2> points, Point2 scale, double thick) : 
            Object(scale, thick), points(points){};
    };
}

#endif
