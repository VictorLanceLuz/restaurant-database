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
    return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Restaurant& restaraunt) {
    return inputStream;
}