#include <iostream>
#include <iomanip>
#include <locale>
#include <random>
#include <algorithm>
#include <cctype>
#include <regex>

#include "Auto.h"

using std::cout;
using std::endl;
using std::regex;

// Initialize the possible values to generate a car list
const vector<std::string> name_list = {"Alpha Romeo", "Audi", "BMW", "Cadillac", "Citroen",
	"Fiat", "Ford", "Honda", "Hyundai", "Kia", "Lexus", "Mazda", "Mercedes-Benz", 
	"Mini", "Mitsubishi", "Nissan", "Opel", "Peugeot", "Porshe", "Renault", "Rolls-Royce", 
	"Saab", "Skoda", "Subaru", "Suzuki", "Toyota", "Volkswagen", "Volvo"};
const vector<std::string> color_list = {"black", "white", "blue", "yellow", "green", "red",
	"orange", "purple", "pink", "brown", "grey"};

// generate and fills all the parameters of the car
void Auto::fill_parameters(Auto& car, int car_id)
{
	// generating values using the Mersenne Vortex
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> name_dist(0, name_list.size() - 1);
	std::uniform_int_distribution<size_t> color_dist(0, color_list.size() - 1);
	std::uniform_int_distribution<int> price_dist(1'000'000, 10'000'000);
	std::uniform_int_distribution<int> speed_dist(180, 300);

	// for rounding up the values
	int price = price_dist(gen);
	int speed = speed_dist(gen);

	// initializing parameters with generated values
	car.id = car_id;
	car.name = name_list.at(name_dist(gen));
	car.price = price - (price % 100'000);
	car.max_speed = speed - (speed % 5);
	car.color = color_list.at(color_dist(gen));
}

// operators and setter for finding the necessary car 
void Auto::set_id(unsigned int id)
{
	this->id = id;
}
bool operator==(const Auto& left, const Auto& right)
{
	if (left.id == right.id)
		return true;
	return false;
}
Auto& Auto::operator=(const Auto& right)
{
	// checking for self-identification
	if (this == &right) {
		return *this;
	}
	id = right.id;
	name = right.name;
	price = right.price;
	max_speed = right.max_speed;
	color = right.color;

	return *this;
}

// getters for all parameters
unsigned int Auto::get_id()
{
	return id;
}
std::string Auto::get_name()
{
	return name;
}
unsigned int Auto::get_price()
{
	return price;
}
unsigned int Auto::get_max_speed()
{
	return max_speed;
}
std::string Auto::get_color()
{
	return color;
}

// For the competent output of warnings
void Auto::show_info_string(std::string&& info) const
{
	cout << "------------------------------------------------------\n"
		<< info << "\n"
		<< "------------------------------------------------------\n";
}
void Auto::show_info_string(std::string& info) const
{
	cout << "------------------------------------------------------\n"
		<< info << "\n"
		<< "------------------------------------------------------\n";
}
void Auto::show_info_string(unsigned int id) const
{
	cout << "------------------------------------------------------\n"
		<< "There are no cars with ID: " << id << "\nPlease select the correct id!\n"
		<< "------------------------------------------------------\n";
}

// Helper interface for users
void Auto::help()
{
	cout << "------------------------------------------------------\n"
		<< "OPTIONS:\n"
		<< "  help\t\t\t\t-\tshow you all commands\n"
		<< "  generate [number]\t\t-\tgenerates the specified number of cars\n"
		<< "  filter [param] [condition]\t-\tfilters cars by the specified parameters\n"
		<< "  buy car [car ID]\t\t-\tbuys a car by id\n"
		<< "  show car list\t\t\t-\tshow the entire list of cars\n"
		<< "  show filter list\t\t-\tshow the filtered list of cars\n"
		<< "  show my car\t\t\t-\tshows customer car\n"
		<< "  exit\t\t\t\t-\tclose the programm\n"
		<< "------------------------------------------------------\n"
		<< "ARGUMENTS:\n"
		<< "  [number] has to be in range [1,10]\n"
		<< "  [param] can be: name/price/speed/color\n"
		<< "  [condition] can be:\n"
		<< "    - car name for param 'name'\n"
		<< "    - maximum price of car for param 'price'\n"
		<< "    - minimum speed of car for param 'speed'\n"
		<< "    - car color for param 'color'\n"
		<< "  [car ID] has to be in car list\n"
		<< "------------------------------------------------------\n";
}

// Generates a list of cars available for purchase
void Auto::car_generation(vector<Auto>& vec, int n)
{
	// checking for entering the range of the number of generated cars
	if (n > 0 && n < 11) {
		vec.clear();
		for (auto i = 1; i <= n; ++i) {
			Auto temp;
			fill_parameters(temp, i);
			vec.push_back(temp);
		}
		is_generated = true;
		show_car_list(vec);
	}
	else {
		show_info_string("Please enter a number from the range [1, 10]");
	}
	
}

// Filter
void Auto::filter(vector<Auto>& car_list, vector<Auto>& filter_list,
	std::string& param, std::string& condition)
{
	// pre-clearing the filtered list
	filter_list.clear();
	// case-insensitive matching
	std::string name = "name";
	std::string color = "color";
	std::string price = "price";
	std::string speed = "speed";

	// name
	if (regex_match(name.begin(), name.end(), regex(param, regex::icase))) {
		std::string compare_str;
		std::transform(condition.begin(), condition.end(),
			condition.begin(), tolower);
		for (auto& i : car_list) {
			std::transform(i.get_name().begin(), i.get_name().end(),
				compare_str.begin(), tolower);
			if (compare_str == condition) {
				filter_list.push_back(i);
			}
		}
		show_filter_car_list(filter_list);
	}
	// price
	else if (regex_match(price.begin(), price.end(), regex(param, regex::icase))) {
		// Checking for the use of digits in condition
		bool digit{ true };
		for (int i = 0; i < condition.size(); ++i) {
			if (!(isdigit(condition[i]))) {
				digit = false;
				break;
			}
		}
		if (digit) {
			if (condition.size() < 18 && std::stoll(condition) > 0) {
				for (auto& i : car_list) {
					if (i.get_price() <= std::stoll(condition)) {
						filter_list.push_back(i);
					}
				}
				show_filter_car_list(filter_list);
			}
			else {
				show_info_string("Use the amount of money less than you specified!");
			}
		}
		else {
			show_info_string("If you use parameter price, use condition as a positive integer");
		}

	}
	// max_speed
	else if (regex_match(speed.begin(), speed.end(), regex(param, regex::icase))) {
		// Checking for the use of digits in condition
		bool digit{ true };
		for (int i = 0; i < condition.size(); ++i) {
			if (!(isdigit(condition[i]))) {
				digit = false;
				break;
			}
		}
		if (digit) {
			if (condition.size() < 4) {
				for (auto& i : car_list) {
					if (i.get_max_speed() >= static_cast<unsigned int>(std::stoi(condition))) {
						filter_list.push_back(i);
					}
				}
				show_filter_car_list(filter_list);
			}
			else {
				show_info_string("Please use the real number speed!");
			}
		}
		else {
			show_info_string("If you use parameter speed, use condition as a positive integer");
		}
	}
	// color
	else if (regex_match(color.begin(), color.end(), regex(param, regex::icase))) {
		std::transform(condition.begin(), condition.end(),
			condition.begin(), tolower);
		for (auto& i : car_list) {
			if (i.get_color() == condition) {
				filter_list.push_back(i);
			}
		}
		show_filter_car_list(filter_list);
	}
	else {
		show_info_string("Please, enter a correct filter!");
	}
}

// The list of cars available for purchase
void Auto::show_car_list(vector<Auto>& vec) const
{
	if (!vec.empty()) {
		// Formatted output
		cout << "------------------------------------------------------\n"
			<< std::left << std::setw(3) << "ID"
			<< std::left << std::setw(15) << "Name"
			<< std::left << std::setw(9) << "Price"
			<< std::left << std::setw(7) << "Speed"
			<< std::left << std::setw(8) << "Color\n";
		cout << "\n";
		for (auto a : vec) {
			cout << std::left << std::setw(3) << a.id
				<< std::left << std::setw(15) << a.name
				<< std::left << std::setw(9) << a.price
				<< std::left << std::setw(7) << a.max_speed
				<< std::left << std::setw(8) << a.color << endl;
		}
		cout << "------------------------------------------------------\n";
	}
	else {
		show_info_string("Car list is empty! Generate a car list!");
	}
}

// The filtered list of cars available for purchase
void Auto::show_filter_car_list(vector<Auto>& filtered_vec) const
{
	if (!filtered_vec.empty()) {
		// Formatted output
		cout << "------------------------------------------------------\n"
			<< std::left << std::setw(3) << "ID"
			<< std::left << std::setw(15) << "Name"
			<< std::left << std::setw(9) << "Price"
			<< std::left << std::setw(7) << "Speed"
			<< std::left << std::setw(8) << "Color\n";
		cout << "\n";
		for (auto a : filtered_vec) {
			cout << std::left << std::setw(3) << a.id
				<< std::left << std::setw(15) << a.name
				<< std::left << std::setw(9) << a.price
				<< std::left << std::setw(7) << a.max_speed
				<< std::left << std::setw(8) << a.color << endl;
		}
		cout << "------------------------------------------------------\n";
	}
	else {
		show_info_string("There are no cars that meet the specified requirements!");

	}
}


