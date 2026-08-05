#include "circle.hpp"
#include "common.hpp"
#include "interpoledBackground.hpp"
#include "object.hpp"

#include <cmath>

namespace pet {
    void Circle::drawObject(Canvas& canvas, RGBColor color, DrawMethod method) {
		switch (method) {
			case DrawMethod::XiaolinWu:
				drawXiaolinWu(this->radius, canvas, color);

				break;
			default:
				drawBresenhan(this->radius, canvas, color);
				break;
		}
    }

	void Circle::drawBresenhan(int radius, Canvas& canvas, RGBColor color) {
        int x = 0;
        int y = radius;
        int d = 1 - radius;

        Pixel p(x, y);
        canvas.add(p, color);
        while(y > x){
            for(int i = -1; i <= 1; i += 2){
                for(int j = -1; j <= 1; j += 2){
                    Pixel p(center.x() + x * i, center.y() + y * j);
                    canvas.add(p, color);
                    p = Pixel(center.x() + y * i, center.y() + x * j);
                    canvas.add(p, color);
                }
            }
            if(d < 0){
                d += 2 * x + 1;
                x++;
            }
            else{
                d += -2 * y + 1;
                y--;
            }
        }
	}

	void Circle::drawXiaolinWu(int radius, Canvas& canvas, RGBColor color) {

		// Função auxiliar responsável por desenhar um único pixel com uma
		// determinada intensidade (alpha), realizando a mistura entre a cor
		// já existente no canvas e a cor da circunferência.
		auto plot = [&](Canvas& canvas, int x, int y, RGBColor color, double alpha)  {

			// Garante que o valor de alpha esteja no intervalo [0, 1].
			alpha = std::clamp(alpha, 0.0, 1.0);

			// Obtém a cor atual armazenada na posição (x, y) do canvas.
			auto current_pixel = canvas.pixel(Pixel(x, y));
			RGBColor pixel_color;

			// Caso exista um pixel nessa posição...
			if(current_pixel.has_value()) {

				// ...interpola linearmente a cor atual com a nova cor,
				// utilizando alpha como fator de mistura.
				pixel_color = InterpoledBackground::linear_interpolation(
					current_pixel.value(), color, alpha);
			}

			// Escreve o pixel resultante no canvas.
			canvas.add(Pixel(x, y), pixel_color);
		};

		// Retorna apenas a parte fracionária de um número.
		// Exemplo: fpart(3.75) = 0.75
		auto fpart = [&](double x) -> double {
			return x - std::floor(x);
		};

		// Retorna o complemento da parte fracionária.
		// Exemplo: rfpart(3.75) = 0.25
		auto rfpart = [&](double x) -> double {
			return 1.0 - fpart(x);
		};

		// Apenas copia o raio para uma variável local.
		int r = radius;

		// Percorre somente o primeiro octante do círculo.
		// Graças à simetria, os demais sete octantes podem ser obtidos
		// espelhando os pontos calculados.
		for (int x = 0; x <= r / std::sqrt(2.0); ++x) {

			// Calcula a coordenada y da circunferência utilizando
			// a equação x² + y² = r².
			double y = std::sqrt(double(r * r - x * x));

			// Parte inteira de y, correspondente ao pixel imediatamente abaixo.
			int yInt = std::floor(y);

			// Parte fracionária de y, usada para determinar a intensidade
			// dos dois pixels vizinhos.
			double frac = fpart(y);

			// ==========================
			// Primeiro octante
			// ==========================

			// Pixel principal (mais próximo da curva).
			plot(canvas, center.x() + x, center.y() + yInt,
				 color, rfpart(frac));

			// Pixel vizinho, cuja intensidade é proporcional à distância
			// da curva até ele.
			plot(canvas, center.x() + x, center.y() + yInt + 1,
				 color, frac);

			// ==========================
			// Segundo octante (espelho horizontal)
			// ==========================

			plot(canvas, center.x() - x, center.y() + yInt,
				 color, rfpart(frac));

			plot(canvas, center.x() - x, center.y() + yInt + 1,
				 color, frac);

			// ==========================
			// Terceiro octante (espelho vertical)
			// ==========================

			plot(canvas, center.x() + x, center.y() - yInt,
				 color, rfpart(frac));

			plot(canvas, center.x() + x, center.y() - yInt - 1,
				 color, frac);

			// ==========================
			// Quarto octante (espelho horizontal + vertical)
			// ==========================

			plot(canvas, center.x() - x, center.y() - yInt,
				 color, rfpart(frac));

			plot(canvas, center.x() - x, center.y() - yInt - 1,
				 color, frac);

			// ==========================
			// Quinto octante
			// (trocando x por y)
			// ==========================

			plot(canvas, center.x() + yInt, center.y() + x,
				 color, rfpart(frac));

			plot(canvas, center.x() + yInt + 1, center.y() + x,
				 color, frac);

			// ==========================
			// Sexto octante
			// ==========================

			plot(canvas, center.x() - yInt, center.y() + x,
				 color, rfpart(frac));

			plot(canvas, center.x() - yInt - 1, center.y() + x,
				 color, frac);

			// ==========================
			// Sétimo octante
			// ==========================

			plot(canvas, center.x() + yInt, center.y() - x,
				 color, rfpart(frac));

			plot(canvas, center.x() + yInt + 1, center.y() - x,
				 color, frac);

			// ==========================
			// Oitavo octante
			// ==========================

			plot(canvas, center.x() - yInt, center.y() - x,
				 color, rfpart(frac));

			plot(canvas, center.x() - yInt - 1, center.y() - x,
				 color, frac);
		}
	}

    void Circle::fillObject(Canvas& canvas, const RGBColor& color) {
		// TODO: missing
    }
} // namespace pet
