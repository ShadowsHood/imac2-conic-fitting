#define _USE_MATH_DEFINES
#include <sil/sil.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>

#include "random.hpp"
#include "conic.hpp"


//---------------- permettre selection des points de controle ----------------

void test_conic_generation(const double& thickness) {
    try {
        // points de contrôle
        std::vector<Eigen::Vector3d> points = {
            {1.0, 2.0, 0.0},
            {2.0, 3.0, 1.0},
            {3.0, 1.0, 1.0},
            {4.0, 4.0, 1.0},
            {5.0, 2.0, 0.0} 
        };
        Conic conic_0(points);
        conic_0.display_props();
        // conic_0.display_control_points();
        export_conic(std::string{"conic_0"}, thickness, conic_0.get_coef());

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

void faisceau_conic(const double& thickness, const Conic& conic_1, const Conic& conic_2, const double& seconds=3.0, const double& fps=1/5.0) {
    // création image faisceau
    sil::Image image{1000/*width*/, 1000/*height*/};
    double const center_x {image.width()/2.0};
    double const center_y {image.height()/2.0};

    // faisceau de conic
    Conic conic_f;

    double t = 0; // temps
    double frames_total = seconds/fps;
    for (int frame=0; frame < frames_total; frame++) {

        // ATTENTION pas de control_points ni de matrix d'eq, on se sert uniquement des coef
        conic_f.set_coef(cos(t)*conic_1.get_coef()/conic_1.get_norm() + sin(t)*conic_2.get_coef()/conic_2.get_norm());

        //couleur
        float r = (std::sin(t + 0) + 1) / 2; // Normaliser entre 0 et 1
        float g = (std::sin(t + 2 * M_PI / 3) + 1) / 2; // Décalage pour le vert
        float b = (std::sin(t + 4 * M_PI / 3) + 1) / 2;

        export_conic(std::string{"faisceau/state"}+std::to_string(frame), thickness, conic_f.get_coef(), {r,g,b});

        double scale = 100; //zoom
        // dessin du faisceau à l'instant t
        for(int x=0; x<image.width(); x++){
            for(int y=0; y<image.height(); y++){
                if(is_in_conic((x-center_x)/scale,(y-center_y)/scale, conic_f.get_coef(), thickness)) image.pixel(x, y) = {r,g,b};
            }
        }

        t += M_PI/frames_total;
    }
    image.save(std::string{"images/output/faisceau/faisceau.png"});
}


int main() 
{
    // faisceau exact trop précis donc on ajoute approximation pour affichage
    double visual_thickness(0.01);

    // test_conic_generation (visual_thickness);

    Conic conic_1, conic_2;
    conic_1.generate_random_control_points(100.0);
    export_conic(std::string{"conic1"}, visual_thickness, conic_1.get_coef());
    conic_2.generate_random_control_points(100.0);
    export_conic(std::string{"conic2"}, visual_thickness, conic_1.get_coef());

    // faisceau_conic(visual_thickness, conic_1, conic_2);

    return 0;
}