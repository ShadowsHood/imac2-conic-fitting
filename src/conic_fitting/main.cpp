#define _USE_MATH_DEFINES
#include <sil/sil.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>

#include "random.hpp"
#include "conic.hpp"

int main() 
{

    try {
        // points de contrôle
        std::vector<Eigen::Vector3d> points = {
            {1.0, 2.0, 1.0},
            {2.0, 3.0, 1.0},
            {3.0, 1.0, 1.0},
            {4.0, 4.0, 1.0},
            {5.0, 2.0, 1.0} 
        };
        Conic conic1(points);

        std::cout << "conic1 coeff : " << conic1.get_coef() << std::endl;
        std::cout << "conic1 matrix size : " << conic1.get_matrix().rows() << " x " << conic1.get_matrix().cols() << std::endl;
        std::cout << "conic1 matrix :\n" << conic1.get_matrix() << std::endl << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }















    // float pi {M_PI};

    // // rayons
    // float r {100.0f};

    // // nombre de cercles
    // int numberCircles {20};

    // sil::Image image{500/*width*/, 500/*height*/};
    // float centreX {image.width()/2.0f};
    // float centreY {image.height()/2.0f};

    // // epaisseur
    // float thickness {2.0f};

    // for (int x{0}; x < image.width(); x++)
    // {
    //     for (int y{0}; y < image.height(); y++)
    //     {
    //         float calc {(x - centreX)*(x - centreX) + (y - centreY)*(y - centreY)};
    //         if (
    //             calc <= r*r && calc >= (r-thickness)*(r-thickness)
    //         ) {
    //             image.pixel(x, y) = glm::vec3{1.0f};
    //         }

    //         for (size_t i = 1; i <= numberCircles; i++)
    //         {
    //             float centreXother = (std::sin(i*2*pi/numberCircles))*r + centreX;
    //             float centreYother = (std::cos(i*2*pi/numberCircles))*r + centreY;
    //             float calc {(x - centreXother)*(x - centreXother) + (y - centreYother)*(y - centreYother)};
    //             if (
    //                 calc <= r*r && calc >= (r-thickness)*(r-thickness)
    //             ) {
    //                 image.pixel(x, y) = glm::vec3{1.0f};
    //             }
    //         }
            
    //     }
    // }
    

    // image.save("images/output/pouet.png");

    return 0;
}