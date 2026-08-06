
#include "canvas.hpp"
#include "common.hpp"
#include "floodFill.hpp"
#include "iterm.hpp"
#include "parser.hpp"

#include <string>

using namespace pet;

void demo();

int main(int argc, char **argv) {

  const std::string arg = argv[1];
  if (argc < 2) { // 1 argumentos
    ITerm iterm(800, 400, "result.ppm");
    iterm.run();
    return 0;
  } else if (argc == 2) {
    if (arg == "demo") {
      demo();
      return 0;
    }

    render(arg);
  }

  return 0;
}

#include "background.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "square.hpp"

void demo() {
  Canvas canvas(800, 400, "file.png", false, ImgType::PNG);
  Background bkg(RGBColor(255, 255, 255, "rgb"));
  for (int j = 0; j < 400; ++j)
    for (int i = 0; i < 800; ++i)
      canvas.add(
			  Pixel(i, j),
			  bkg.sample(double(i) / 800.0,
			  double(j) / 400.0));

  Line line(Point2(0, 0), Point2(600, 200), Point2(1,1), 10.0);
  // line.drawObject(canvas, RGBColor(0, 0, 0, "rgb"), DrawMethod::XiaolinWu);

  Line line2(Point2(600, 0), Point2(0, 200), Point2(1,1), 10.0);
  line2.drawObject(canvas, RGBColor(0, 0, 0, "rgb"), DrawMethod::Bresenhan);

  // Circle c1(80, Point2(400,200));
  // c1.drawObject(canvas, RGBColor(0, 0, 0, "rgb"), DrawMethod::Bresenhan);
  Circle c2(100, Point2(400,200));
  // c2.drawObject(canvas, RGBColor(0, 0, 0, "rgb"), DrawMethod::XiaolinWu);

  // Rectangle rec(Point2(100, 100), Point2(300,200));
  // rec.drawObject(canvas, RGBColor(0, 0, 0, "rgb"));

  Square square = Square::fromCorner(Point2(200,100), 100);
  square = Square::fromCenter(Point2(400,200), 100);
  // square.drawObject(canvas, RGBColor(0, 0, 0, "rgb"));

  Circle c1(100, {400, 200});
  c1.drawObject(canvas, RGBColor{.0,.0,.0, "RGB"}, DrawMethod::Bresenhan);
  FloodFill fill_tool;
  fill_tool.fill(canvas, {400, 200}, RGBColor{0.5,.0,.5});

  canvas.export_img();

} // namespace
