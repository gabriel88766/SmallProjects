#pragma once
#include "color.hpp"
#include <cstdint>

namespace graphics {
    struct Image{
        uint32_t *buffer;
        int width, height;
        ~Image();
        Image(int h, int w);
        void setPixel(const int &x, const int &y, const unsigned char &R, const unsigned char &G, const unsigned char &B);
        void setPixel(const int &x, const int &y, const unsigned char &R, const unsigned char &G, const unsigned char &B, const unsigned char &A);
        void setPixel(const int &x, const int &y, const Color &c);
        void setBackground(const Color &c);
    };
}