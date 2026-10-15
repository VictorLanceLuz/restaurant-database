#include "Restaurant.hpp"
#include <sstream>

Restaurant::Restaurant() : id(0) {}

Restaurant::Restaurant(int id, std::string name, std::string cuisine) : id(id), name(move(name)), cuisine(move(cuisine)) {}

void Restaurant::addMenuItem(const std::string& menuItemEntry) {
    menuItems.push_back(menuItemEntry); 
}

int Restaurant::getId() const {
    return id;
}

const std::string& Restaurant::getName() const {
    return name;
}

const std::string& Restaurant::getCuisine() const {
    return cuisine;
}

const std::vector<std::string>& Restaurant::getMenu() const {
    return menuItems;
}

std::ostream& operator<<(std::ostream& outputStream, const Restaurant& restaurant) {
    outputStream << restaurant.id << '#' << restaurant.name << '#' << restaurant.cuisine << '#' << restaurant.menuItems.size();
    for (const auto& item : restaurant.menuItems) {
        outputStream << '#' << item;
    }
    return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Restaurant& restaraunt) {
    std::string rawLine;
    std::string field; 
    int itemCount; 

    restaraunt.menuItems.clear(); // to prevent mixup of old and new menu items. 

    if(!getline(inputStream, rawLine)) {
        return inputStream;
    }
    std::stringstream lineStream(rawLine);

    getline(lineStream, field, '#'); // extract id
    restaraunt.id = stoi(field);

    getline(lineStream, restaraunt.name, '#'); // extract name and cuisine.
    getline(lineStream, restaraunt.cuisine, '#');

    getline(lineStream, field, '#');
    itemCount = stoi(field); 

    for (int i = 0; i < itemCount; ++i) {
        if (!getline(lineStream, field, '#')) {
            return inputStream; 
        }
        restaraunt.menuItems.push_back(field); 
    }
    return inputStream; 
}