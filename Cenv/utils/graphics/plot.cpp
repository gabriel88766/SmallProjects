#include "plot.hpp"
#include <stdio.h>

namespace graphics{
    void Graph::addPoint(double x, double y){
        points.push_back({x, y});
    }
    void Graph::plot(Image &img){
        if(points.size() != 0){
            const int &width = img.width - 10;
            const int &heigth = img.height - 10;
            std::sort(points.begin(), points.end());
            xi = points[0].first, xf = points.back().first;
            yi = yf = points[0].second;
            for(int i=1;i<points.size();i++){
                yi = std::min(yi, points[i].second);
                yf = std::max(yf, points[i].second);
            }
            xi = -0.01, xf = 999.1;
            yi = 0, yf = 65535;
            // yi -= 0.01;
            // yf += 0.01;
            // xi -= 0.01;
            // xf += 0.01;
            //0 = xi, 
            int p0 = 0;
            for(int y=0;y<heigth + 10;y++){
                for(int x = 0; x<width + 10;x++){
                    img.setPixel(x, y, Color::CYAN);
                }
            }
            fflush(stdout);
            for(int x=0;x<width;x++){
                double x_now = x;
                x_now /= width - 1;
                x_now *= (xf - xi);
                x_now += xi;
                while(p0 + 1 < points.size() && points[p0 + 1].first  + 1e-6 < x_now) p0 += 1;
                double y_now = points[p0].second + (points[p0+1].second - points[p0].second) * (x_now - points[p0].first) / (points[p0+1].first - points[p0].first);
                int plot_y = ((y_now - yi) / (yf - yi)) * heigth;
                if(plot_y == heigth) plot_y--;
                plot_y = heigth - plot_y - 1;
                //NO WAY
                plot_y = ((points[p0].second)/yf) * heigth;
                plot_y = heigth - plot_y - 1;
                img.setPixel(x + 5, plot_y + 5, Color::BLACK);
            }
            fflush(stdout);
        }
    }
}