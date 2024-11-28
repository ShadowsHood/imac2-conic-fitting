#define _USE_MATH_DEFINES
#include <sil/sil.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>

#include "random.hpp"
#include "conic.hpp"


//---------------- permettre selection des points de controle ----------------

void test_conic_generation() {
    try {
        // points de contrôle
        std::vector<Eigen::Vector3d> points = {
            {1.0, 2.0, 1.0},
            {2.0, 3.0, 1.0},
            {3.0, 1.0, 1.0},
            {4.0, 4.0, 1.0},
            {5.0, 2.0, 0.0} 
        };
        Conic conic1(points);
        conic1.display_props();
        // conic1.display_control_points();

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

int main() 
{
    // test_conic_generation ();
    // generation conic
    Conic conic_1, conic_2;
    conic_1.generate_random_control_points(1000.0);
    conic_2.generate_random_control_points(1000.0);

    // création image
    sil::Image image{1000/*width*/, 1000/*height*/};
    float centreX {image.width()/2.0f};
    float centreY {image.height()/2.0f};

    // faisceau de conic
    Conic conic_f;
    double t = 1.2; // compris entre 0 et pi
    // ATTENTION pas de control_points ni de matrix d'eq, on se sert uniquement des coef
    conic_f.set_coef(cos(t)*conic_1.get_coef()/conic_1.get_norm() + sin(t)*conic_2.get_coef()/conic_2.get_norm());

    //couleur
    float r = (std::sin(t + 0) + 1) / 2; // Normaliser entre 0 et 1
    float g = (std::sin(t + 2 * M_PI / 3) + 1) / 2; // Décalage pour le vert
    float b = (std::sin(t + 4 * M_PI / 3) + 1) / 2;

    









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