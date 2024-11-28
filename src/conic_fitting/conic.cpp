#include "conic.hpp"
#include "random.hpp"

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

bool is_in_conic(const double x, const double y, const Eigen::VectorXd & coef, double const& thickness) {
    return 
        (coef[0]*x*x + coef[1]*x*y + coef[2]*y*y + coef[3]*x + coef[4]*y + coef[5] 
            < thickness) 
        && 
        (coef[0]*x*x + coef[1]*x*y + coef[2]*y*y + coef[3]*x + coef[4]*y + coef[5] 
            > -thickness);
}

void export_conic(const std::string& name, const double& thickness, const Eigen::VectorXd& conic_coef, const glm::vec3& color) {
    sil::Image image{1000/*width*/, 1000/*height*/};

    double const center_x{image.width()/2.0};
    double const center_y{image.height()/2.0};

    double scale = 100; //zoom

    for(int x=0; x<image.width(); x++){
        for(int y=0; y<image.height(); y++){
            //poitionne le pixel hypotetiquement dans le repère de la conique pour le calcul
            if(is_in_conic((x-center_x)/scale,(y-center_y)/scale, conic_coef, thickness)) image.pixel(x, y) = color;
        }
    }


    image.save(std::string{"images/output/conic/"+ name + ".png"});
    image.save(std::string{"images/output/conic/temp.png"});
}

// =================================================================================================
// Conic
// =================================================================================================

Conic::Conic():
    m_control_points(std::vector<Eigen::Vector3d>(5)),
    m_matrix(Eigen::MatrixXd::Zero(5,6)),
    m_coef(Eigen::VectorXd(6))
    {};

Conic::Conic(const std::vector<Eigen::Vector3d>& control_points) {
        if (control_points.size() != 5) throw std::invalid_argument("5 control point required");
        m_matrix=Eigen::MatrixXd::Zero(5,6);
        m_coef=Eigen::VectorXd(6);
        m_control_points = control_points;
        this->update_props();
    }

void Conic::set_control_points(std::vector<Eigen::Vector3d> const& control_points) { 
    this->m_control_points = control_points;
    this->update_props();
};

// =================================================================================================
// Calculate

void Conic::fill_matrix_from_control_points(){
    for (size_t i=0; i < m_control_points.size(); i++) {
        for (size_t j=0; j < m_coef.size(); j++) {
            m_matrix(i, j) = point_to_conic_equation(m_control_points[i])[j];
        }
    }
}

void Conic::calculate_coef() {
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(m_matrix, Eigen::ComputeThinU | Eigen::ComputeThinV);
    m_coef = svd.matrixV().rightCols(1);
}

double Conic::get_norm() const{
    return std::pow(m_coef[0]*m_coef[0] + m_coef[1]*m_coef[1] + m_coef[2]*m_coef[2] + m_coef[3]*m_coef[3] + m_coef[4]*m_coef[4] + m_coef[5]*m_coef[5],0.5);
}

// =================================================================================================
// Displays

void Conic::display_props() const {
    std::cout << "matrix size : " << m_matrix.rows() << " x " << m_matrix.cols() << std::endl;
    std::cout << "matrix :\n" << m_matrix << std::endl;
    std::cout << "coeff : \n" << m_coef << std::endl << std::endl;
}

void Conic::display_control_points() const {
    for (size_t i=0; i < m_control_points.size(); i++) {
        std::cout << "point " << i << " : " << m_control_points[i] << std::endl;
    }
}

// =================================================================================================
// Generate

void Conic::generate_random_control_points(double randomScale) {
    for (size_t i=0; i < m_control_points.size(); i++) {
        // equivalent points => singular matrix => circle
        // m_control_points[i] = Eigen::Vector3d::Random() * randomScale; 

        //  random points no negative
        // m_control_points[i] = Eigen::Vector3d{random_float(randomScale,2*randomScale),random_float(randomScale,2*randomScale),random_float(randomScale,2*randomScale)};
        
        m_control_points[i] = Eigen::Vector3d{random_float(-randomScale,randomScale),random_float(-randomScale,randomScale),random_float(-randomScale,randomScale)};
    }
    this->update_props();
}