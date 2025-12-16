// Yenika Rojas 
// December 9,2025 
// Project 3

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include "GroceryItem.h"

using namespace std;

typedef map<string, GroceryItem*> GroceryMap; // Map with item as key & GroceryItem pointer as value

// Deletes allocated GroceryItem and clears map
void ClearMap(GroceryMap& items) {
	for (auto it = items.begin(); it != items.end(); ++it) {
		delete it->second;
	}
	items.clear();
}
// Loads inventory.txt & builds fresh map of GroceryItem
bool LoadFile(GroceryMap& items) {
	ClearMap(items);

	ifstream inFS("inventory.txt");
	if (!inFS.is_open()) {
		cout << "ERROR: Could not open inventory.txt\n";
		return false;

	}

	string itemName;

	// Read each item from file
	while (inFS >> itemName) {
		// If item exists, increment quantity
		if (items.count(itemName) > 0) {
			items.at(itemName)->addItem();
		}
		else {
			// Otherwise, create a new GroceryItem object
			GroceryItem* newItem = new GroceryItem(itemName);
			items.emplace(itemName, newItem);
		}
	}
	inFS.close();
	return true;
}
void PrintAll(GroceryMap& items) {
	for (auto it = items.begin(); it != items.end(); ++it) {
		cout << it->first << " " << it->second->getQuantity() << endl;
	}
}

// Prints text bases histogram using astericks
void PrintHistogram(GroceryMap& items) {
	for (auto it = items.begin(); it != items.end(); ++it) {
		cout << it->first << " ";

		for (int i = 0; i < it->second->getQuantity(); i++) {
			cout << "*"; // Print one '*' per quantity
		}
		cout << endl;
	}
}

// Writes frequencies to frequency.dat on exit
void WriteFrequencyFile(GroceryMap& items) {
	ofstream outFS("frequency.dat");

	if (!outFS.is_open()) {
		cout << "ERROR: Could not write frequency.dat\n";
		return;
	}

	// Write in the format Item Quantity
	for (auto it = items.begin(); it != items.end(); ++it) {
		outFS << it->first << " " << it->second->getQuantity();
	}

	outFS.close();
}

// Main Program - Menu

int main() {

	GroceryMap items; 
	int choice = 0;

	while (choice != 4) {

		cout << "\n=============================\n";
		cout << "      Corner Grocery Menu      \n";
		cout << "\n=============================\n";
		cout << "1. Look up an item\n";
		cout << "2. Print frequency of all items\n";
		cout << "3. Print histogram of all items\n";
		cout << "4. Exit Program\n";
		cout << "Enter choice (1-4): ";

		// Validate correct input
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Try again.\n";
			choice = 0;
			continue;
		}

		// Option 1: Frequency
		if (choice == 1) {

			if (!LoadFile(items)) continue;

			string searchItem;
			cout << "Enter item name: ";
			cin >> searchItem;

			if (items.count(searchItem) > 0) {
				cout << searchItem << " appears "
					<< items.at(searchItem)->getQuantity()
					<< " time(s).\n";
			}
			else {
				cout << searchItem << " does not appear in the file.\n";
			}
		}
		// Option 2: Print items and frequencies
		else if (choice == 2) {
			if (!LoadFile(items)) continue;
			PrintAll(items);
		}
		// Option 3: Print histogram
		else if (choice == 3) {
			if (!LoadFile(items)) continue;
			PrintHistogram(items);
		}
		// Option 4: Exit program and create back up file
		else if (choice == 4) {
			if (LoadFile(items)) {
				WriteFrequencyFile(items);
			}
			cout << "Exiting program. Goodbye!\n";
		}
		// Any other option
		else {
			cout << "Please enter options between 1 and 4.\n";
		}
	}
	ClearMap(items); // Clear memory before exiting program

	return 0;
}