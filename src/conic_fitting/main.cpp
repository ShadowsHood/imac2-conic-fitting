#define _USE_MATH_DEFINES
#include <sil/sil.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>

#include "random.hpp"
#include "conic.hpp"

void test_conic_generation(const double& thickness) {
    try {
        // points de contrôle
        std::vector<Eigen::Vector3d> points = {
            {1.0, 2.0, 1.0},
            {2.0, 3.0, 1.0},
            {3.0, 1.0, 1.0},
            {4.0, 4.0, 1.0},
            {5.0, 2.0, 1.0},
            {6.0, 12.0, 1.0}
        };
        std::vector<Eigen::Vector3d> points2 = {
            {3.0, 6.0, 1.0},
            {1.0, 8.0, 1.0},
            {12.0, 1.0, 1.0},
            {4.0, 18.0, 1.0},
            {20.0, 6.0, 1.0}
        };
        Conic conic_0(points);
        conic_0.display_props();
            conic_0.save_points("conic_0_test");
        conic_0.set_control_points(points2);
            conic_0.load_points("conic_0_test");
        conic_0.display_props();
        // conic_0.display_control_points();

        export_conic(std::string{"conic_0"}, thickness, conic_0.get_coef());

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

void faisceau_conic(const double& thickness, const Conic& conic_1, const Conic& conic_2, const int& nb_frames=10) {
    // création image faisceau
    sil::Image image{1000/*width*/, 1000/*height*/};
    double const center_x {image.width()/2.0};
    double const center_y {image.height()/2.0};

    // faisceau de conic
    Conic conic_f;

    double t = 0; // temps
    for (int frame=0; frame < nb_frames; frame++) {

        // ATTENTION pas de control_points ni de matrix d'eq, on se sert uniquement des coef
        conic_f.set_coef(cos(t)*conic_1.get_coef()/conic_1.get_norm() + sin(t)*conic_2.get_coef()/conic_2.get_norm());

        //couleur
        float r = (1+ std::sin(t)) /2; // 0 et 1
        float g = (1+ std::sin(t+2*M_PI/3)) /2;
        float b = (1+ std::sin(t+4*M_PI/3)) /2;

        export_conic(std::string{"faisceau/state/state"}+std::to_string(frame), thickness, conic_f.get_coef(), {r,g,b});

        double scale = 75; //zoom
        // dessin du faisceau à l'instant t
        for(int x=0; x<image.width(); x++){
            for(int y=0; y<image.height(); y++){
                if(is_in_conic((x-center_x)/scale,(y-center_y)/scale, conic_f.get_coef(), thickness)) image.pixel(x, y) = {r,g,b};
            }
        }

        t += M_PI/nb_frames;
    }
    image.save(std::string{"images/output/conic/faisceau/faisceau.png"});
}

bool user_choice() {
    char user_gen_choice;
    std::cout << "Do you want to make the conics random (O) or load the preconfigured conics (n): ";
    std::cin >> user_gen_choice;
        if (std::tolower(user_gen_choice) != 'o' && std::tolower(user_gen_choice) != 'n') {
        std::cerr << "Invalid input. Please enter '1' or '0'." << std::endl;
        return 1;
    }
    return (std::tolower(user_gen_choice) == 'o');
}

int main() 
{
    // faisceau exact trop précis donc on ajoute approximation pour affichage
    double visual_thickness(0.01);

    // test_conic_generation (visual_thickness);

    Conic conic_1, conic_2;

    bool rand_generation = user_choice();

    if(rand_generation) {
        conic_1.generate_random_control_points(100.0);
            // conic_1.save_points("conic_1"); // sauvegarde des points de contrôle pour conic_1 pour les recharger après si besoin
        conic_2.generate_random_control_points(100.0);
            // conic_2.save_points("conic_2");
    } else {
        conic_1.load_points("conic_1");
        conic_2.load_points("conic_2");
    }   

    export_conic(std::string{"conic_1"}, visual_thickness, conic_1.get_coef());
    export_conic(std::string{"conic_2"}, visual_thickness, conic_2.get_coef());

    faisceau_conic(visual_thickness, conic_1, conic_2, 20);
    std::cout << "Faisceau de coniques généré" << std::endl;

    return 0;
}