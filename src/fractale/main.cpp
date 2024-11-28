// #define _USE_MATH_DEFINES

#include <sil/sil.hpp>
#include <iostream>
// #include "random.hpp"
// #include <cmath>
#include <complex>

                // Convertir RGB en HSL
                glm::vec3 rgbToHsl(const glm::vec3& rgb) {
                    float minVal = std::min(std::min(rgb.r, rgb.g), rgb.b);
                    float maxVal = std::max(std::max(rgb.r, rgb.g), rgb.b);
                    float delta = maxVal - minVal;

                    float h = 0.0f;
                    float s = 0.0f;
                    float l = (maxVal + minVal) / 2.0f;

                    if (delta != 0.0f) {
                        s = (l < 0.5f) ? (delta / (maxVal + minVal)) : (delta / (2.0f - maxVal - minVal));

                        if (rgb.r == maxVal) {
                            h = (rgb.g - rgb.b) / delta + ((rgb.g < rgb.b) ? 6.0f : 0.0f);
                        } else if (rgb.g == maxVal) {
                            h = (rgb.b - rgb.r) / delta + 2.0f;
                        } else if (rgb.b == maxVal) {
                            h = (rgb.r - rgb.g) / delta + 4.0f;
                        }

                        h /= 6.0f;
                    }

                    return glm::vec3(h, s, l);
                }

                // Convertir HSL en RGB
                glm::vec3 hslToRgb(const glm::vec3& hsl) {
                    float h = hsl.r;
                    float s = hsl.g;
                    float l = hsl.b;

                    float c = (1.0f - std::abs(2.0f * l - 1.0f)) * s;
                    float x = c * (1.0f - std::abs(std::fmod(h * 6.0f, 2.0f) - 1.0f));
                    float m = l - 0.5f * c;

                    float r, g, b;

                    if (h < 1.0f / 6.0f) {
                        r = c;
                        g = x;
                        b = 0.0f;
                    } else if (h < 2.0f / 6.0f) {
                        r = x;
                        g = c;
                        b = 0.0f;
                    } else if (h < 3.0f / 6.0f) {
                        r = 0.0f;
                        g = c;
                        b = x;
                    } else if (h < 4.0f / 6.0f) {
                        r = 0.0f;
                        g = x;
                        b = c;
                    } else if (h < 5.0f / 6.0f) {
                        r = x;
                        g = 0.0f;
                        b = c;
                    } else {
                        r = c;
                        g = 0.0f;
                        b = x;
                    }

                    return glm::vec3{r + m, g + m, b + m};
                }

int main()
{
    sil::Image image{1000/*width*/, 1000/*height*/};
    // std::complex<float> z{3.f, 2.f}; // Définis le nombre z = 3 + 2*i
    float width {static_cast<float>(image.width())};
    float height {static_cast<float>(image.height())};

    float maxIterationsTest {50};
    float nbInteressantMin {-2.f};
    float nbInteressantMax {2.f};
    float plageValues {nbInteressantMax - nbInteressantMin};

    for (float x{0}; x < width; x++)
    {
        for (float y{0}; y < height; y++)
        {
            std::complex<float> c{x * plageValues/width -2, y * plageValues/height -2};
            std::complex<float> z{0.f};
            float iterations {0};

            while(iterations < maxIterationsTest) {
                z = z * z + c;
                iterations++;

                if (std::abs(z) > 2) {
                    // image.pixel(x, y) = glm::vec3{iterations/maxIterationsTest};
                    // image.pixel(x, y).r = iterations/maxIterationsTest;  
                    image.pixel(x, y) = hslToRgb(glm::vec3{x/width, 1.f, iterations/maxIterationsTest});
                    // image.pixel(x, y) = hslToRgb(glm::vec3{iterations/(maxIterationsTest/1.5), 1.f, iterations/maxIterationsTest});
                    break;
                }
            }

            if (iterations == maxIterationsTest) image.pixel(x, y) = glm::vec3{1.f};
            
        }
    }



    image.save("output/pouet.png");
    image.save("final/fractale.png");
}