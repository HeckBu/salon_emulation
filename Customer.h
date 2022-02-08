#pragma once
#include "Auto.h"

class Customer : public Auto
{
	// Customer parameters
private:
	// default, the customer does not have a car
	bool is_owner{ false }; 
public:
	// List of cars purchased by the buyer
	std::vector<Auto> owner_cars;

	// main program features 
	// for customer
	void show_customer_car() const; 
	void buy_car(std::vector<Auto>& vec, std::vector<Auto>& filter_vec, std::string& id);
};

