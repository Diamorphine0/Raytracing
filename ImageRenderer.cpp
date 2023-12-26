//
// Created by tudor on 10/12/23.
//

#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(int height, int width){
    image_height = height;
    image_width = width;

    pixel_colors = std::vector< std::vector< Color >> (image_height,
                                                       std::vector< Color >(image_width, Color(0, 0, 0)));

}

void ImageRenderer::reset_pixels() {
    pixel_colors = std::vector< std::vector< Color >> (image_height,
                                                       std::vector< Color >(image_width, Color(0, 0, 0)));
}

bool ImageRenderer::set_pixel(int pixel_row, int pixel_column, const Color &color) {
    if(pixel_row < 0 || pixel_row >= image_height)
        return false;
    if(pixel_column < 0 || pixel_column >= image_width)
        return false;
    pixel_colors[pixel_row][pixel_column] = color;
    return true;
}

bool ImageRenderer::set_all_pixels(const std::vector<std::vector<Color>> &colors) {
    if(colors.size() != image_height)
        return false;
    for (const auto & colors_row : colors){
        if (colors_row.size() != image_width)
            return false;
    }
    pixel_colors = colors;
    return true;
}

void ImageRenderer::render_image(const std::string &file_image) {
    std::ofstream  outFile(file_image);

    if(outFile.is_open()){
        std::cerr<<"Ok?\n";
    }
    outFile<<"P3\n";
    outFile<<image_width<<" "<<image_height<<" "<<255<<"\n";
    for(int i = 0; i < image_height; i++){
        for(int j = 0; j < image_width; j++){
            outFile<<pixel_colors[i][j]<<"\n";

        }
    }
    std::cerr<<"Done printing!\n"<<image_height<<" "<<image_width<<"\n"<<pixel_colors[0][0]<<"\n";
    outFile.flush();
}


