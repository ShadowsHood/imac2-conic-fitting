#define _USE_MATH_DEFINES
#include <sil/sil.hpp>
#include <iostream>
// #include "random.hpp"
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

namespace glm{
    bool operator<(vec3 v1, vec3 v2){
        if (v1.x != v2.x) {
            return v1.x < v2.x;
        } else if (v1.y != v2.y) {
            return v1.y < v2.y;
        } else if (v1.z != v2.z) {
            return v1.z < v2.z;
        } else {
            return false;
        }
    }
}

// Fonction pour trouver les n valeurs les plus présentes dans le tableau initial
std::vector<glm::vec3> mostFrequentValues(const std::vector<glm::vec3>& pixels, int n) {
    // Map pour stocker la fréquence de chaque valeur
    std::map<glm::vec3, int> frequencyMap {};

    // Compter la fréquence de chaque valeur dans le tableau
    for (const auto& pixel : pixels) {
        frequencyMap[pixel]++;
    }

    // Créer un vecteur pour stocker les paires (valeur, fréquence)
    std::vector<std::pair<glm::vec3, int>> frequencyPairs {};
    for (const auto& pair : frequencyMap) {
        frequencyPairs.push_back(pair);
    }

    // Trier le vecteur en fonction de la fréquence (du plus grand au plus petit)
    std::sort(frequencyPairs.begin(), frequencyPairs.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Créer un vecteur pour stocker les n valeurs les plus fréquentes
    std::vector<glm::vec3> result {};
    
    for (int i = 0; i < n && i < frequencyPairs.size(); ++i) {
        result.push_back(frequencyPairs[i].first);
    }

    return result;
}

glm::vec3 closestColor (const glm::vec3& color, const std::vector<glm::vec3>& references) {

    // Initialiser avec une distance maximale possible
    float minDistance {std::numeric_limits<float>::max()};
    glm::vec3 closestColor {};

    // Parcourir le tableau de couleurs
    for (const auto& referenceColor : references) {
        // Calculer la distance entre la couleur cible et la couleur de référence
        float distance = glm::distance(color, referenceColor);

        // Mettre à jour la couleur la plus proche
        if (distance < minDistance) {
            minDistance = distance;
            closestColor = referenceColor;
        }
    }

    return closestColor;
}



int main()
{

    sil::Image image{"images/photo.jpg"};

    int color_number = 3;

    std::vector<glm::vec3> most_freq_values = mostFrequentValues(image.pixels(), color_number);

    for (glm::vec3& color : image.pixels())
    {
        glm::vec3 newColor {closestColor(color, most_freq_values)};
        color = newColor;
    }


    image.save("output/pouet.png");
    image.save("final/kmeans.png");
}