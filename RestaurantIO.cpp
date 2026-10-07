#include "RestaurantIO.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>



void addRestaurant(std::vector<Restaurant>& database) {
    int restaurantId;
    int menuItemCount;
    std::string restaurantName;
    std::string cuisineType;

    database.push_back(restaurant); 
}

void displayRestaurants(const std::vector<Restaurant>& database) {
    for (const auto& restaurant : database) {
        std::cout << "\nID: " << restaurant.getId()
                  << "\nName: " << restaurant.getName()
                  << "\nCuisine: " << restaurant.getCuisine()
                  << "\nMenu:\n";
        for (const auto& menuItemEntry : restaurant.getMenu()) {
            std::cout << "  - " << menuItemEntry << '\n'; 
        }
    }
}

bool loadDatabase(std::vector<Restaurant>& database, const std::string& filename) {
    std::ifstream inputFile(filename);
    Restaurant restaurant; 
}

void saveDatabase(const std::vector<Restaurant>& database, const std::string& filename) {
    
}