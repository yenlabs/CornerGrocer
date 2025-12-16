// Yenika Rojas 
// December 9,2025 
// Project 3


#ifndef GROCERY_ITEM_H
#define GROCERY_ITEM_H

#include <string>

class GroceryItem 
{
public:
	// Constructor-sets items with name and sets quantity to 1
	GroceryItem(const std::string& name);
	
	std::string getName() const; // Returns the item name
	int getQuantity() const; // Returns how many times item appears

	void addItem(); // Increases the quantity by 1

private:
	std::string name; // Name of grocery item
	int quantity; // Number of times the items is on the list
};

#endif

