// Yenika Rojas 
// December 9,2025 
// Project 3

#include "GroceryItem.h"

// Contructor- sets item name and quantity to 1
GroceryItem::GroceryItem(const std::string& name) {
	this->name = name;
	this->quantity = 1; 
}

// Return name of item
std::string GroceryItem::getName() const {
	return name;
}

// Return current quantity
int GroceryItem::getQuantity() const {
	return quantity;
}
// Increment quantity by 1 each time item appears
void GroceryItem::addItem() {
	quantity++;
}
