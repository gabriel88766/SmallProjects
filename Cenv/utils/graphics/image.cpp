#include "image.hpp"

//Low level definition of a image, based on ARGB uint_32
namespace graphics{
    Image::~Image(){
        delete[] buffer;
    }

    Image::Image(int h, int w){
        width = w;
        height = h;
        buffer = new uint32_t[h*w];
    }

    void Image::setPixel(const int &x, const int &y, const unsigned char &R, const unsigned char &G, const unsigned char &B){
        setPixel(x, y, R, G, B, 0xFF);
    }
    void Image::setPixel(const int &x, const int &y, const unsigned char &R, const unsigned char &G, const unsigned char &B, const unsigned char &A){
        buffer[y * width + x] =  A + (R << 8) | (G << 16) | (B << 24);
    }
    void Image::setPixel(const int &x, const int &y, const Color &c){
        setPixel(x, y, c.R, c.G, c.B, c.A);
    }
    void Image::setBackground(const Color &c){
        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++){
                setPixel(x, y, c);
            }
        }
    }
}