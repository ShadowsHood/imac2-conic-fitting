#include "conic.hpp"

Eigen::VectorXd point_to_conic_equation(const Eigen::Vector3d & point){
    Eigen::VectorXd eq(6);
    eq << point[0]*point[0], 
        point[0]*point[1],
        point[1]*point[1],
        point[0]*point[2],
        point[1]*point[2],
        point[2]*point[2];
    return eq;
}

Conic::Conic():
    m_coef(Eigen::VectorXd(6)), 
    m_control_points(std::vector<Eigen::Vector3d>(5)),
    m_matrix(Eigen::MatrixXd::Zero(5,6)) 
    {};

Conic::Conic(const std::vector<Eigen::Vector3d>& control_points) {
        if (control_points.size() != 5) throw std::invalid_argument("5 control point required");
        m_control_points = control_points;
        m_matrix=Eigen::MatrixXd::Zero(5,6);
        this->fill_matrix_from_control_points();
        this->calculate_coef();
    }

void Conic::fill_matrix_from_control_points(){
    for (size_t i=0; i < m_control_points.size(); i++) {
        for (size_t j=0; j < m_control_points[i].size(); j++) {
            m_matrix(i, j) = point_to_conic_equation(m_control_points[i])[j];
        }
    }
}

void Conic::calculate_coef() {
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(m_matrix, Eigen::ComputeThinU | Eigen::ComputeThinV);
    m_coef = svd.matrixV().rightCols(1);
}