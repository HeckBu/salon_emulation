#include <iostream>
#include <iomanip>
#include <locale>

#include "Customer.h"

// shows to customer what last car has been buying
void Customer::show_customer_car() const
{
	if (is_owner) {
		// Formatted output
		std::cout << "------------------------------------------------------\n"
			<< "The list of my cars:\n"
			<< std::left << std::setw(15) << "Name"
			<< std::left << std::setw(9) << "Price"
			<< std::left << std::setw(7) << "Speed"
			<< std::left << std::setw(8) << "Color\n";
		std::cout << "\n";
		for (auto a : owner_cars) {
			std::cout << std::left << std::setw(15) << a.get_name()
				<< std::left << std::setw(9) << a.get_price()
				<< std::left << std::setw(7) << a.get_max_speed()
				<< std::left << std::setw(8) << a.get_color() << std::endl;
		}
		std::cout << "------------------------------------------------------\n";
	}
	else {
		show_info_string("Customer has no car!");
	}
}

// the buying car by a customer
void Customer::buy_car(std::vector<Auto>& vec, 
		std::vector<Auto>& filter_vec, std::string& id)
{
	// Checking for the use of digits in condition
	bool digit{ true };
	for (int i = 0; i < id.size(); ++i) {
		if (!(isdigit(id[i]))) {
			digit = false;
			break;
		}
	}
	if (digit) {
		if (id.size() < 10 && std::stoi(id) > 0) {
			Auto temp;
			temp.set_id(std::stoi(id));

			if (!vec.empty()) {
				if (std::find(vec.begin(), vec.end(), temp) != vec.end()) {
					// Find car with entered id
					auto it = std::find(vec.begin(), vec.end(), temp);
					temp = *it;

					// Adding the car to the list purchased by the buyer
					owner_cars.push_back(temp);

					// remove the purchased car from the lists
					vec.erase(std::find(vec.begin(), vec.end(), temp));
					if (find(filter_vec.begin(), filter_vec.end(), temp) != filter_vec.end()) {
						filter_vec.erase(std::find(filter_vec.begin(), filter_vec.end(), temp));
					}

					// Now customer has a car
					is_owner = true;
					// display a list of machines to the user
					show_customer_car();

					// checking whether there are no more cars in the list
					if (vec.empty()) {
						is_generated = false;
					}
				}
				else {
					show_info_string(std::stoi(id));
				}
			}
			else {
				show_info_string("For buying a car, please generate the car list!");
			}
		}
		else {
			show_info_string(std::stoi(id));
		}
	}
	else {
		show_info_string("Please, use the correct id");
	}

	
	
}
