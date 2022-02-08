#pragma once
#include <iostream>
#include <sstream>

#include "Auto.h"
#include "Customer.h"

using std::cin;
using std::cout;
using std::endl;

void start() {
	// Greeting and showing the user a hint 
	Customer customer;
	cout << "Welcome to our salon!\n";
	customer.help();

	// Creating a list of cars and a filtered list of cars in the salon
	vector<Auto> car_list;
	vector<Auto> filter_car_list;

	// strings and vector for splitting input data
	std::string input, parse;
	std::string param, condition;
	vector<std::string> split;

	// string saying that there are no cars in the list
	std::string empty_list{ "The list is empty! Please generate a list of cars!" };

	// for close the program
	bool work = true;

	while (work) {
		std::getline(cin, input);
		std::istringstream is(input);

		// checking for an empty string
		if (input.empty()) {
			customer.show_info_string("Enter the command!");
			continue;
		}

		// parse commands
		split.clear();
		while (is >> parse) {
			split.push_back(parse);
		}

		// command help
		if (split.at(0) == "help") {
			customer.help();
		}
		// command exit
		else if (split.at(0) == "exit") {
			work = false;
			customer.show_info_string("Thank you for visiting our salon!");
			break;
		}
		// command generate
		else if (split.at(0) == "generate") {
			// Checking for the use of 2 words in a command generate
			if (split.size() == 2) {
				// Checking for the use of digits in second word
				bool digit{ true };
				for (int i = 0; i < split.at(1).size(); ++i) {
					if (!(isdigit(split.at(1)[i]))) {
						digit = false;
						break;
					}
				}
				// the [number] has to be less than 11
				if (digit && split.at(1).size() < 3) {
					param = split.at(1);
					customer.car_generation(car_list, std::stoi(param));
				}
				else {
					customer.show_info_string("The number have to be in range [1,10]!");
				}
			}
			else {
				customer.show_info_string("Please, enter correct generate!");
			}
		}
		// command filter
		else if (split.at(0) == "filter") { 
			// Checking for the use of 3 words in a command filter
			if (split.size() == 3) {
				param = split.at(1);
				condition = split.at(2);
				if (customer.is_generated == true) {
					customer.filter(car_list, filter_car_list, param, condition);
				}
				else {
					customer.show_info_string(empty_list);
				}
			}
			else {
				customer.show_info_string("Please, enter a correct filter!");
			}
		}
		// command show
		else if (split.at(0) == "show") {
			// Checking for the use of 3 words in a command show
			if (split.size() == 3) {
				// output car list
				if (split.at(1) == "car" && split.at(2) == "list") {
					if (customer.is_generated == true) {
						customer.show_car_list(car_list);
					}
					else {
						customer.show_info_string(empty_list);
					}
				}
				// output filter list
				else if (split.at(1) == "filter" && split.at(2) == "list") {
					if (customer.is_generated == true) {
						customer.show_filter_car_list(filter_car_list);
					}
					else {
						customer.show_info_string(empty_list);
					}
				}
				// output list of customer cars
				else if (split.at(1) == "my" && split.at(2) == "car") {
					if (customer.is_generated == true) {
						customer.show_customer_car();
					}
					else {
						customer.show_info_string(empty_list);
					}
				}
				else {
					customer.show_info_string("The program cannot show this. Check the command for errors!");
				}
			}
			else {
				customer.show_info_string("Please, enter a correct show!");
			}
			
		}
		// command buy
		else if (split.at(0) == "buy") {
			// Checking for the use of 3 words in a command show 
			// and the second word is car
			if (split.size() == 3 && split.at(1) == "car") {
				if (!split.at(2).empty()) {
					param = split.at(2);
					if (customer.is_generated == true) {
						customer.buy_car(car_list, filter_car_list, param);
					}
					else {
						customer.show_info_string(empty_list);
					}
				}
				else {
					customer.show_info_string("Enter the correct purchase with the correct id!");
				}
			}
			else {
				customer.show_info_string("Please, enter a correct buy!");
			}
		}
		// non-existent command
		else {
			customer.show_info_string("The program does not know such a command. See the available commands in help.");
		}
	}
}

int main() {

	// start the program
	start();

	return 0;
}