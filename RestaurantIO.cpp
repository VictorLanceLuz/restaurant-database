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

    std::cout << "Enter restaurant ID: ";
    std::cin >> restaurantId;  
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard leftover newline

    std::cout << "Enter restaurant name: ";
    std::getline(std::cin, restaurantName);
    std::cout << "Enter cuisine type: ";
    std::getline(std::cin, cuisineType);

    Restaurant restaurant(restaurantId, restaurantName, cuisineType);

    std::cout << "Enter the number of menu items: ";
    std::cin >> menuItemCount;
    if (std::cin.fail() || menuItemCount < 0) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid number.\n";
        return;
    }

    for (int i = 0; i < menuItemCount; ++i) {
        std::cout << "Enter item " << (i + 1) << " name: ";
        std::string itemName;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove buffer.
        std::getline(std::cin, itemName); 
        
        std::cout << "Enter item " << (i + 1) << " price: ";
        double itemPrice;
        std::cin >> itemPrice; 
        if (std::cin.fail() || itemPrice < 0) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid price.\n";
            return;
        }

        std::stringstream itemEntryStream; 
        itemEntryStream << std::fixed << std::setprecision(2);
        itemEntryStream << itemName << " " << itemPrice; 
        restaurant.addMenuItem(itemEntryStream.str()); 
    }

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
    if (inputFile.is_open()) {
        while (inputFile >> restaurant) {
            database.push_back(restaurant); 
        }
        return true; 
    } else {
        std::cerr << "[WARN] Could not open " << filename << " for reading.\n";
        return false;
    }
}

void saveDatabase(const std::vector<Restaurant>& database, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const auto& restaurant : database) {
            outputFile << restaurant << std::endl;
        }
        outputFile.close();
    } else {
        std::cerr << "[ERR] Could not open " << filename << " for writing.\n";
    }
}