#pragma once
#include "image.hpp"
#include <vector>
#include <algorithm>

namespace graphics{
    struct Graph{
        std::vector<std::pair<double, double>> points;
        double xi, xf, yi, yf; //after plot
         // new features?
        // int padding_left = 0, padding_right = 0, padding_top = 0, padding_bottom = 0;
        // bool display_number = false;
        // bool display_lines = false;
        // int digits = 0;//digits after .
        //core
        void addPoint(double x, double y);
        void plot(Image &img);
    };
} 
