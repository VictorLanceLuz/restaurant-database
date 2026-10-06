#pragma once
#include <string>
#include <vector>

class Restaurant {
private:
    int id;
    std::string name;
    std::string cuisine;
    std::vector<std::string> menuItems;
public:
    Restaurant();
    Restaurant(int id, std::string name, std::string cuisine);
    
    void addMenuItem(const std::string& menuItemEntry);
    int getId() const;
    const std::string& getName() const;
    const std::string& getCuisine() const; 
    const std::vector<std::string>& getMenu() const;
    friend std::ostream& operator<<(std::ostream& outputStream, const Restaurant& restaurant);
    friend std::istream& operator>>(std::istream& inputStream, Restaurant& restaurant);
};