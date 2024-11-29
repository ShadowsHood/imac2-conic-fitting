#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <sil/sil.hpp>
#include <fstream>

Eigen::VectorXd point_to_conic_equation(const Eigen::Vector3d & point);

bool is_in_conic(const double x, const double y, const Eigen::VectorXd & coef, double const& thickness);

void export_conic(const std::string& name, const double& thickness, const Eigen::VectorXd& conic_coef, const glm::vec3& color = {1.0,1.0,1.0});

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

        // Save & load control points
        void save_points(const std::string &filename) const;

        void load_points(const std::string &filename);

};