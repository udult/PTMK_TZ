// Employees.cpp - Employee class source code

#include <regex>
#include <iostream>
#include <exception>
#include "../include/common.hpp"
#include "../include/Employee.hpp"

Employee::Employee(const std::string& name, const std::string& date, const std::string& gen) 
	: fullname{name}, birthdate{date}, gender{gen} { } 

void Employee::save_into_db() const 
{
	std::regex date_format(R"(^\d{4}-\d{1,2}-\d{1,2}$)");

	if (!std::regex_match(birthdate, date_format))
		throw std::invalid_argument("Wrong date format: has to be YYYY-MM-DD");

	if (gender != "male" && gender != "female")
		throw std::invalid_argument("Invalid gender value: has to be male/female");

	std::string request = "INSERT INTO employees (fullname, birthdate, gender) VALUES ('" + fullname + "','" + birthdate + "','" + gender + "')";

	exec_sql_request(request);
		
	std::cout << "employee has been inserted successfully" << std::endl;
}

int Employee::calculate_age() const
{
	int birth_year  = stoi(birthdate.substr(0, 4));
	int birth_month = stoi(birthdate.substr(5, 2));
	int birth_day   = stoi(birthdate.substr(8, 2));

	int current_year, current_month, current_day;
	
	current_date(current_year, current_month, current_day);

	int age = current_year - birth_year;

	if (current_month < birth_month || (current_month == birth_month && current_day < birth_day))
		age--;

	return age;
}

const std::string& Employee::get_fullname() const { return fullname; }
	
const std::string& Employee::get_birthdate() const { return birthdate; }

const std::string& Employee::get_gender() const { return gender; }

/**/
