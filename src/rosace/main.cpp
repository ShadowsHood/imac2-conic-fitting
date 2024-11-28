#define _USE_MATH_DEFINES
#include <sil/sil.hpp>
#include <iostream>
#include <cmath>
    
int main()
{
    float pi {M_PI};

    // rayons
    float r {100.0f};

    // nombre de cercles
    int numberCircles {20};

    sil::Image image{500/*width*/, 500/*height*/};
    float center_x {image.width()/2.0f};
    float center_y {image.height()/2.0f};

    // epaisseur
    float thickness {2.0f};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float calc {(x - center_x)*(x - center_x) + (y - center_y)*(y - center_y)};
            if (
                calc <= r*r && calc >= (r-thickness)*(r-thickness)
            ) {
                image.pixel(x, y) = glm::vec3{1.0f};
            }

            for (size_t i = 1; i <= numberCircles; i++)
            {
                float center_xother = (std::sin(i*2*pi/numberCircles))*r + center_x;
                float center_yother = (std::cos(i*2*pi/numberCircles))*r + center_y;
                float calc {(x - center_xother)*(x - center_xother) + (y - center_yother)*(y - center_yother)};
                if (
                    calc <= r*r && calc >= (r-thickness)*(r-thickness)
                ) {
                    image.pixel(x, y) = glm::vec3{1.0f};
                }
            }
            
        }
    }
    

    image.save("images/output/pouet.png");
    // image.save("images/final/rosace.png");
}