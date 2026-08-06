#include "line.hpp"
#include "canvas.hpp"
#include "common.hpp"
#include "interpoledBackground.hpp"
#include <cstdlib>
#include <utility>

namespace pet {
void Line::drawObject(Canvas &canvas, RGBColor color, DrawMethod method) {
  switch (method) {
    case DrawMethod::Bresenhan: {
      drawBresenhan(start, end, canvas, color);
    
      int half = thick / 2;

      for (int t = 1; t <= half; t++){
        drawBresenhan(Point2(start.x(), start.y()-t), Point2(end.x(), end.y()-t), canvas, color);
        drawBresenhan(Point2(start.x(), start.y()+t), Point2(end.x(), end.y()+t), canvas, color);
      }

      break;
    }

    case DrawMethod::BresenhanMidpoint: {
      drawMidpoint(start, end, canvas, color);
      
      int half = thick / 2;

      for (int t = 1; t <= half; t++){
        drawMidpoint(Point2(start.x(), start.y()-t), Point2(end.x(), end.y()-t), canvas, color);
        drawMidpoint(Point2(start.x(), start.y()+t), Point2(end.x(), end.y()+t), canvas, color);
      }

      break;
    }

    case DrawMethod::XiaolinWu: {
      drawXiaolinWu(start, end, canvas, color);
      break;
    }
  }
}

void Line::drawBresenhan(Point2 p1, Point2 p2, Canvas &canvas, RGBColor color){
  // TODO: missing thickness
    int x0 = p1.x(), y0 = p1.y();
    int x1 = p2.x(), y1 = p2.y();
    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

	// ======
    // Swap axes if steep
    if (steep) {
      std::swap(x0, y0);
      std::swap(x1, y1);
    }

    // Ensure left->right
    if (x0 > x1) {
      std::swap(x0, x1);
      std::swap(y0, y1);
    }
	// ======

    int dx = x1 - x0;
    int dy = std::abs(y1 - y0);
    int error = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
      if (steep) {
        canvas.add(Pixel(y, x), color);
      } else {
        canvas.add(Pixel(x, y), color);
      }
      error -= dy;
      if (error < 0) {
        y += ystep;
        error += dx;
      }
    }
}

void Line::drawMidpoint(Point2 p1, Point2 p2, Canvas &canvas, RGBColor color){
  // TODO: missing thickness
    int x = p1.x(); //> "Erro"
    int y = p1.y(); //> "Erro"

    int dx = p2.x() - p1.x(); //> Define o "diferencial" dos x
    int dy = p2.y() - p1.y(); //> Define o "diferencial" dos y

    int stepX = dx >= 0 ? 1 : -1; //> Define o passo que x irá percorrer (1:
                                  // direita, -1: esquerda)
    int stepY =
        dy >= 0
            ? 1
            : -1; //> Define o passo que y irá percorrer (1: baixo, -1: cima)
    dx = std::abs(dx);
    dy = std::abs(dy);

    canvas.add(Pixel(x, y), color);

    if (dy <= dx) {
      int d = 2 * dy - dx;

      int stepE = 2 * dy;         //> se leste for escolhido
      int stepNE = 2 * (dy - dx); //> se nordeste for escolhido

      while (x != p2.x()) {
        x += stepX;

        if (d < 0) { //> se leste for escolhido
          d += stepE;
        } else { //> se nordeste for escolhido
          d += stepNE;
          y += stepY;
        }
        canvas.add(Pixel(x, y), color);
      }
    }

    else {
      int d = 2 * dx - dy;

      int stepN = 2 * dx;
      int stepNE = 2 * (dx - dy);

      while (y != p2.y()) {
        y += stepY;

        if (d < 0) { //> se leste for escolhido
          d += stepN;
        } else { //> se nordeste for escolhido
          d += stepNE;
          x += stepX;
        }
        canvas.add(Pixel(x, y), color);
      }
    }
}

// void drawXiaolinWu(Point2 p1, Point2 p2, Canvas &canvas, RGBColor color){
  //TODO
// }
void Line::drawXiaolinWu(Point2 p1, Point2 p2, Canvas &canvas, RGBColor color) {

  // Função auxiliar para desenhar um pixel com uma intensidade (alpha) específica.
  // A intensidade será usada para misturar a cor da linha com a cor que já existe
  // no canvas.
  auto plot = [&](int px, int py, double intensity) {

    // Garante que a intensidade fique entre 0 e 1.
    intensity = std::clamp(intensity, 0.0, 1.0);

    // Obtém a cor atual do pixel.
    auto pixel_opt = canvas.pixel(Pixel(px, py));

    // Caso o pixel esteja fora do canvas, simplesmente ignora.
    if (!pixel_opt)
      return;

    // Mistura a cor existente com a cor da linha utilizando a intensidade.
    RGBColor blended = InterpoledBackground::linear_interpolation(
        pixel_opt.value(), color, intensity);

    // Escreve o resultado no canvas.
    canvas.add(Pixel(px, py), blended);
  };

  // Verifica se a reta é "íngreme".
  //
  // Se |dy| > |dx| significa que ela varia mais no eixo Y do que no X.
  // Nesse caso é mais fácil percorrer Y do que X.
  bool steep = std::abs(p2.y() - p1.y()) > std::abs(p2.x() - p1.x());

  // Copiamos as coordenadas para doubles porque o algoritmo utiliza
  // valores fracionários durante toda a execução.
  double x0 = p1.x();
  double y0 = p1.y();
  double x1 = p2.x();
  double y1 = p2.y();

  // Caso a reta seja íngreme, trocamos X por Y.
  //
  // Assim todas as retas passam a ser tratadas como "mais horizontais",
  // simplificando o restante do algoritmo.
  if (steep) {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }

  // Garante que sempre desenhamos da esquerda para a direita.
  //
  // Isso evita um gradiente negativo na iteração principal e torna
  // o algoritmo único para qualquer direção da reta.
  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  // Diferença horizontal.
  double dx = x1 - x0;

  // Diferença vertical.
  double dy = y1 - y0;

  // Inclinação da reta.
  //
  // gradient = Δy / Δx
  //
  // Caso dx seja zero (reta perfeitamente vertical),
  // evita divisão por zero.
  double gradient = (dx == 0) ? 0.0 : dy / dx;

  // =====================================================
  // Primeiro endpoint
  // =====================================================

  // Primeiro pixel inteiro mais próximo da coordenada inicial.
  int xEnd = std::round(x0);

  // Calcula a posição Y correspondente exatamente nesse X.
  double yEnd = y0 + gradient * (xEnd - x0);

  // Quanto do primeiro pixel deve realmente ser desenhado.
  //
  // Como a linha começa no meio de um pixel,
  // apenas parte dele deve receber cor.
  double xGap = 1.0 - std::fmod(x0 + 0.5, 1.0);

  // Coordenadas inteiras do primeiro pixel.
  int xPixel1 = xEnd;

  // Parte inteira da coordenada Y.
  int yPixel1 = static_cast<int>(std::floor(yEnd));

  // Se trocamos os eixos anteriormente,
  // precisamos inverter novamente na hora de desenhar.
  if (steep) {

    // Pixel inferior.
    plot(yPixel1, xPixel1,
         (1 - (yEnd - yPixel1)) * xGap);

    // Pixel superior.
    plot(yPixel1 + 1, xPixel1,
         (yEnd - yPixel1) * xGap);

  } else {

    plot(xPixel1, yPixel1,
         (1 - (yEnd - yPixel1)) * xGap);

    plot(xPixel1, yPixel1 + 1,
         (yEnd - yPixel1) * xGap);
  }

  // Guarda a coordenada Y da próxima coluna.
  double intery = yEnd + gradient;

  // =====================================================
  // Segundo endpoint
  // =====================================================

  // Mesmo procedimento realizado para o primeiro endpoint.
  xEnd = std::round(x1);

  yEnd = y1 + gradient * (xEnd - x1);

  // Agora usamos apenas a fração restante do pixel final.
  xGap = std::fmod(x1 + 0.5, 1.0);

  int xPixel2 = xEnd;

  int yPixel2 = static_cast<int>(std::floor(yEnd));

  if (steep) {

    plot(yPixel2, xPixel2,
         (1 - (yEnd - yPixel2)) * xGap);

    plot(yPixel2 + 1, xPixel2,
         (yEnd - yPixel2) * xGap);

  } else {

    plot(xPixel2, yPixel2,
         (1 - (yEnd - yPixel2)) * xGap);

    plot(xPixel2, yPixel2 + 1,
         (yEnd - yPixel2) * xGap);
  }

  // =====================================================
  // Corpo principal da reta
  // =====================================================

  // Percorre todas as colunas entre os dois endpoints.
  for (int x = xPixel1 + 1; x < xPixel2; x++) {

    // Parte inteira da posição Y atual.
    int y = static_cast<int>(std::floor(intery));

    // Parte fracionária da posição Y.
    //
    // Exemplo:
    // intery = 15.3
    // y      = 15
    // frac   = 0.3
    double frac = intery - y;

    if (steep) {

      // Pixel inferior recebe a intensidade complementar.
      plot(y, x, 1.0 - frac);

      // Pixel superior recebe a intensidade proporcional.
      plot(y + 1, x, frac);

    } else {

      plot(x, y, 1.0 - frac);

      plot(x, y + 1, frac);
    }

    // Atualiza a posição Y para a próxima coluna.
    intery += gradient;
  }
}
} // namespace pet
