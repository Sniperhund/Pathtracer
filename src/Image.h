//
// Created by Lucas Täkker on 14/05/2024.
//

#pragma once

#include "Math/Vector3.h"
#include "Math/Utility.h"

#include <vector>
#include <string>
#include <iostream>
#include <lodepng.h>

class Image {
public:
    Image(int width, int height) {
        m_pixels.resize(width * height * 4);
        m_width = width;
        m_height = height;
    }

    void SetPixel(int x, int y, Vector3 color) {
        m_pixels[4 * m_width * y + 4 * x + 0] = int(255.999 * Clamp(0, 1, LinearToGamma(color.x)));
        m_pixels[4 * m_width * y + 4 * x + 1] = int(255.999 * Clamp(0, 1, LinearToGamma(color.y)));
        m_pixels[4 * m_width * y + 4 * x + 2] = int(255.999 * Clamp(0, 1, LinearToGamma(color.z)));
        m_pixels[4 * m_width * y + 4 * x + 3] = 255;
    }

    void Save(std::string outputFile) {
        unsigned int error = lodepng::encode(outputFile, m_pixels, m_width, m_height);

        if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
    }

private:
    inline float LinearToGamma(float linear) {
        if (linear > 0)
            return sqrt(linear);

        return 0;
    }

    std::vector<unsigned char> m_pixels;
    int m_width, m_height;
};
