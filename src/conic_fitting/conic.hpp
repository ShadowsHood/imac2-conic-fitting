#pragma once
#include <iostream>
#include <Eigen/Dense>

Eigen::VectorXd point_to_conic_equation(const Eigen::Vector3d & point);

class Conic
{
    private:
        // vector of 5 control points Pi(xi,yi,wi)
        std::vector<Eigen::Vector3d> m_control_points;
        // matrix of xi^2, xi*yi, yi^2, xi*w, yi*w, w*w with i(number of control points) = 5
        Eigen::MatrixXd m_matrix;
        // vector of a,b,c,d,e,f
        Eigen::VectorXd m_coef;

    public:
        // Constructors and Destructors
        Conic();
        Conic(const std::vector<Eigen::Vector3d>& control_points);
        Conic(const Conic & conic):
            m_control_points(conic.m_control_points),
            m_matrix(conic.m_matrix),
            m_coef(conic.m_coef)
        {};
        inline ~Conic(){};

        // Getters and Setters
            inline std::vector<Eigen::Vector3d> get_control_points() const { return this->m_control_points;}
            inline Eigen::VectorXd get_coef() const { return this->m_coef;}
            inline Eigen::MatrixXd get_matrix() const { return this->m_matrix;}
        void set_control_points(std::vector<Eigen::Vector3d> const& control_points);
        inline void set_coef(Eigen::VectorXd const& coef){this->m_coef = coef;}; // utilisation pour le faisceau de conique

        // Calculate
        void fill_matrix_from_control_points();
        void calculate_coef();
        inline void update_props(){this->fill_matrix_from_control_points(); this->calculate_coef();};
        double get_norm() const;
        
        // Displays
        void display_props() const;
        void display_control_points() const;

        // Generate
        void generate_random_control_points(double randomScale);
        
        // void save_image(std::string name, double & epaisseur, float R = 1.0, float G = 1.0, float B = 1.0)
        // {
        //     sil::Image image{1000/*width*/, 1000/*height*/};

        //     int const centerX{(image.width()-1)/2};
        //     int const centerY{(image.height()-1)/2};

        //     double scale = 100;

        //     for(int x{0}; x<image.width(); x++){
        //         for(int y{0}; y<image.height(); y++){
        //             if(respect_conic((x-centerX)/scale,(y-centerY)/scale,this->m_coef, epaisseur))
        //             {
        //                 image.pixel(x, y) = glm::vec3{R,G,B};
        //             } 
        //         }
        //     }

        
        //     image.save(std::string{"src/Conic/output/"+ name + ".png"});
        // }

};