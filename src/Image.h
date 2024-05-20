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
        Resize(width, height);
    }

    void Resize(int width, int height) {
        m_pixels.resize(width * height * 4);
        m_width = width;
        m_height = height;
    }

    void SetPixel(int x, int y, Vector3 color) {
        if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
            std::cerr << "SetPixel error: Coordinates (" << x << ", " << y << ") are out of bounds." << std::endl;
            return;
        }

        m_pixels[4 * m_width * y + 4 * x + 0] = int(255.999 * Clamp(0, 1, LinearToGamma(color.x)));
        m_pixels[4 * m_width * y + 4 * x + 1] = int(255.999 * Clamp(0, 1, LinearToGamma(color.y)));
        m_pixels[4 * m_width * y + 4 * x + 2] = int(255.999 * Clamp(0, 1, LinearToGamma(color.z)));
        m_pixels[4 * m_width * y + 4 * x + 3] = 255;
    }

    void Save(std::string outputFile) {
        unsigned int error = lodepng::encode(outputFile, m_pixels, m_width, m_height);

        if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
    }

    std::vector<unsigned char> GetRawPixels() { return m_pixels; }
private:
    inline float LinearToGamma(float linear) {
        if (linear > 0)
            return sqrt(linear);

        return 0;
    }

    std::vector<unsigned char> m_pixels = std::vector<unsigned char>();
    int m_width = -1, m_height = -1;
};
