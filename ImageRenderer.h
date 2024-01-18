//
// Created by tudor on 10/12/23.
//

#ifndef RAY_TRACING_IMAGERENDERER_H
#define RAY_TRACING_IMAGERENDERER_H

#include "Utilities.hpp"
#include <vector>
#include <fstream>

class ImageRenderer {
public:
    ImageRenderer(int height, int width);

    int get_height() const { return image_height; }
    int get_width() const { return image_width; }

    //Returns if operation was succesful
    bool set_pixel(int pixel_row, int pixel_column, const Color &color);
    bool set_all_pixels(const std::vector<std::vector<Color>> &colors);

    void reset_pixels();

    void render_image();

private:
    int image_height;   // Rendered image height
    int image_width; // width

    std::vector< std::vector<Color>> pixel_colors;
};


#endif //RAY_TRACING_IMAGERENDERER_H
