#include <iostream>
#include "RestaurantIO.hpp"

int main() {
    std::vector<Restaurant> restaurantDatabase;
    const std::string databaseFile = "restaurants.txt";

    loadDatabase(restaurantDatabase, databaseFile);

    int userChoice;
    do {
        std::cout << "\n--- Restaurant Database ---\n"
                  << "1. Add Restaurant\n"
                  << "2. View Restaurants\n"
                  << "3. Save & Exit\n"
                  << "Choice: ";
        std::cin >> userChoice; 
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid choice.\n";
            continue; 
        }

        switch (userChoice) {
            case 1:
                addRestaurant(restaurantDatabase);
                break;
            case 2:
                displayRestaurants(restaurantDatabase);
                break;
            case 3:
                saveDatabase(restaurantDatabase, databaseFile);
                std::cout << "Data saved. Goodbye!\n";
                break;
            default:
                std::cout << "Please choose a valid option (1-3).\n"; 
                break;
        }
    } while (userChoice != 3);
    return 0; 
}