/**
 * @file canvas.hpp
 * @brief Implementação da classe que descreve a tela do programa
 * @author Heitor Campos() 
 * @author Arthur Skeete()
 * @author Gabriel Carvalho()
 * @details Esta classe guarda as informações da imagem e permite a exportação da mesma.
 * @date 25/05/2026()
 */

#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "common.hpp"
#include "lodepng/lodepng.h"
#include "export_img.hpp"
#include <string>
#include <vector>

namespace pet {
    enum class ImgType { //> Tipo da imagem exportada
            PPM3=0,
            PNG,
        };

            /**
              * @class Canvas
              * @brief Classe responsável por guardar as informações principais sobre a imagem 
              * e exportá-la para os tipos PNG e PPM3
              */
    class Canvas {
        private:

        std::string filename;
        std::vector<RGBColor> buffer;
        int img_width;
        int img_height;
        ImgType type;
        bool gamma_correction;

        public:
        
            /**
              * @brief Construtor parametrizado
              * @param w Largura da imagem.
              * @param h Altura da imagem.
              * @param fn Nome do arquivo de exportação.
              *
              */

            Canvas(const int &w, const int &h, const std::string &fn, ImgType imgType = ImgType::PPM3, bool gc = false) 
            : filename(fn), img_width(w), img_height(h), type(imgType), gamma_correction(gc)
            {
                buffer.resize(w*h);
            };

            int get_width() const { return img_width; }
            int get_height() const { return img_height; }

            const std::vector<RGBColor>& data() const { return buffer; }

            /**
              * @brief Função que desenha um pixel na imagem
              * @param pixel Posição do pixel desenhado.
              * @param color Nova cor do pixel.
              */
            void add(const Pixel& pixel, const RGBColor& color){
                if(pixel.x() < 0 || pixel.x() >= img_width || pixel.y() < 0 || pixel.y() >= img_height) return;

                buffer[pixel.y() * img_width + pixel.x()] = color;
            };
            
            /**
             * @brief Função que exporta a imagem armazenada
             */
            bool export_img() const {
                return ExportImg::exportPPM3(filename, buffer, img_width, img_height, false);
            };
	};
};

#endif
