#pragma once
#include <cstdint>
//Defines a Color, format ARGB (A | (R << 8) | (G << 16) | (B << 24)) or (RGB >> 8) | 0xFF
namespace graphics{
    struct Color {
        uint8_t A = 0xFF;
        uint8_t R = 0;
        uint8_t G = 0;
        uint8_t B = 0;

        Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 0xFF)
            : R(R), G(G), B(B), A(A) {}
        
        constexpr uint32_t toARGB() const noexcept {
            return (uint32_t(B) << 24) | (uint32_t(G) << 16) | (uint32_t(R) << 8) | uint32_t(A);
        }
        static const Color BLUE;
        static const Color BLACK;
        static const Color RED;
        static const Color GREEN;
        static const Color WHITE;
        static const Color YELLOW;
        static const Color MAGENTA;
        static const Color CYAN;
        static const Color GRAY;
    };

}