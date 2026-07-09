#ifndef FOREVERLAND_COLOR_H
#define FOREVERLAND_COLOR_H

#include <string>

struct color {
    int r=0, g=0, b=0;
    int cmdColor = 0;
    enum type {
        RGB,
        CMD,
    } type;

    static color hexToRgb(const std::string& hexStr);
    std::string getColor() const {
        return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }

    color() = default;
    color(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
        type = RGB;
    }
    color(int cmdColor) {
        this->cmdColor = cmdColor;
        type = CMD;
    }
    color(const std::string& hexStr) {
        color c = hexToRgb(hexStr);
        this->r = c.r;
        this->g = c.g;
        this->b = c.b;
        type = RGB;
    }
};
std::string getColor(int r, int g, int b);
std::string getColor(color c);
std::string getFakeColor(color c);

color hexToRgb(const std::string& hexStr);

std::string getGradientString(color start, color end, const std::string& str);

#endif //FOREVERLAND_COLOR_H
