#pragma once
#include <string>
#include <vector>

using std::vector;

class Auto
{
private:
	// For generayion and filling the car list
	void fill_parameters(Auto& car, int car_id);

protected:
	// Car parameters
	unsigned int id;
	std::string name;
	unsigned int price;
	unsigned int max_speed;
	std::string color;


public:
	// operators for the Auto data type
	friend bool operator==(const Auto& left, const Auto& right);
	Auto& operator=(const Auto& right);
	
	// Getters and setters
	void set_id(unsigned int id);
	unsigned int get_id();
	std::string get_name();
	unsigned int get_price();
	unsigned int get_max_speed();
	std::string get_color();

	// For the competent output of warnings
	bool is_generated{ false };
	void show_info_string(std::string&& info) const;
	void show_info_string(std::string& info) const;
	void show_info_string(unsigned int id) const;

	// main program features 
	// for car salon
	void help(); 
	void car_generation(vector<Auto>& vec, int n); 
	void filter(vector<Auto>& car_list, vector<Auto>& filter_list, 
				std::string& param, std::string& condition);
	void show_car_list(vector<Auto>& vec) const; 
	void show_filter_car_list(vector<Auto>& filtered_vec) const;
};
