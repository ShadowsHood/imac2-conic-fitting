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
        Conic();
        Conic(const std::vector<Eigen::Vector3d>& control_points);
        inline ~Conic(){};

        inline void set_coef(Eigen::VectorXd v) { this->m_coef = v;}
            inline Eigen::VectorXd get_coef() const { return this->m_coef;}
        inline void set_matrix(Eigen::MatrixXd v) { this->m_matrix = v;}
            inline Eigen::MatrixXd get_matrix() const { return this->m_matrix;}

        void fill_matrix_from_control_points();
        void calculate_coef();
        
        // double get_norm() const
        // {
        //     return std::pow(m_coef(0)*m_coef(0) + m_coef(1)*m_coef(1) + m_coef(2)*m_coef(2) + m_coef(3)*m_coef(3) + m_coef(4)*m_coef(4) + m_coef(5)*m_coef(5),0.5);
        // }

        // Eigen::VectorXd get_coef(){ return this->m_coef;}
        // std::vector<Eigen::Vector3d> get_point(){ return this->m_pointList;}
        // Eigen::MatrixXd get_proj_matrix() {return this->A;}

        // void set_point(std::vector<Eigen::Vector3d> & v)
        // {
        //     this->m_pointList = v;
        // }

        // void set_coef_precise(int const& indice, double & value)
        // {
        //     this->m_coef(indice) = value;
        // }

        // void set_coef(Eigen::VectorXd v)
        // {
        //     this->m_coef = v;
        // }

        // void display_conic() const{
        //     std::cout << "Les coefs de votre conique sont : " << "\n";
        //     std::cout << this->m_coef << "\n";
        //     std::cout << "Voici votre matrice de projection : " << "\n";
        //     std::cout << this->A << "\n";
        // }

        // void set_equation_from_matrix()
        // {
        //     Eigen::JacobiSVD<Eigen::MatrixXd> svd (this->A, Eigen::ComputeThinU|Eigen::ComputeFullV);
        //     this->m_coef = svd.matrixV().rightCols(1);
        // }

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

        // void conic_setup_random(double & randomScale)
        // {

        //     std::vector<Eigen::Vector3d> randomList{
        //         Eigen::Vector3d{generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale)},
        //         Eigen::Vector3d{generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale)},
        //         Eigen::Vector3d{generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale)},
        //         Eigen::Vector3d{generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale)},
        //         Eigen::Vector3d{generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale),generateRandomDouble(-randomScale, randomScale)}
        //     };
        //     this->set_point(randomList);
        //     this->create_proj_matrix();
        //     this->set_equation_from_matrix();
        // }

};