#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

struct City {
    int id;
    double x;
    double y;
};

double calculateDistance(const City& city1, const City& city2) {
    double dx = city1.x - city2.x;
    double dy = city1.y - city2.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::pair<std::vector<int>, double> greedyTSP(std::vector<City>& cities) {
    int n = cities.size();
    std::vector<int> path;
    path.reserve(n);

    std::vector<bool> visited(n, false);
    visited[0] = true;
    path.push_back(0);

    double totalCost = 0.0;

    for (int i = 0; i < n - 1; ++i) {
        int nearestCity = -1;
        double minDistance = std::numeric_limits<double>::max();
        for (int j = 0; j < n; ++j) {
            if (!visited[j]) {
                double distance = calculateDistance(cities[path[i]], cities[j]);
                if (distance < minDistance) {
                    nearestCity = j;
                    minDistance = distance;
                }
            }
        }
        if (nearestCity != -1) {
            path.push_back(nearestCity);
            visited[nearestCity] = true;
            totalCost += minDistance;
        }
    }

    totalCost += calculateDistance(cities[path[n - 1]], cities[0]);

    return { path, totalCost };
}

int main() {
    std::ifstream inputFile("tsp_85900_1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 1;
    }

    std::vector<City> cities;
    std::string line;
    std::getline(inputFile, line); // Skip the first line
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        City city;
        iss >> city.id >> city.x >> city.y;
        cities.push_back(city);
    }

    inputFile.close();

    auto result = greedyTSP(cities);

    std::cout << "Optimal Path: ";
    for (int cityIndex : result.first) {
        std::cout << cities[cityIndex].id << " ";
    }
    std::cout << std::endl;

    std::cout << "Optimal Cost: " << result.second << std::endl;

    return 0;
}
